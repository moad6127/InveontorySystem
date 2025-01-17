// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemBase.h"
#include "Components/SphereComponent.h"
#include "Item/ItemObject.h"
#include "InventoryData.h"
#include "Interface/InventoryPlayerInterface.h"


AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh");
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	ItemMesh->SetSimulatePhysics(true);

	Sphere = CreateDefaultSubobject<USphereComponent>("ItemCollision");
	Sphere->SetupAttachment(ItemMesh);

}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	InitializeItem(UItemObject::StaticClass());
	Sphere->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnSphereOverlap);
}

void AItemBase::InitializeItem(const TSubclassOf<UItemObject> BaseItem)
{
	if (ItemDataTable && !DesiredItemID.IsNone())
	{
		const FItemData* ItemData = ItemDataTable->FindRow<FItemData>(DesiredItemID, DesiredItemID.ToString());
		ItemObject = NewObject<UItemObject>(this, BaseItem);
		//TODO : ItemValueSet
		ItemObject->ID = ItemData->ID;
		ItemObject->SlotType = ItemData->SlotType;
		ItemObject->ItemNumbericData = ItemData->ItemNumbericData;
		ItemObject->Asset = ItemData->Asset;
		ItemObject->ItemName = ItemData->ItemName;
		ItemObject->SetItemSizeX(ItemSizeX);
		ItemObject->SetItemSizeY(ItemSizeY);

		ItemMesh->SetStaticMesh(ItemData->Asset.Mesh);
	}

}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 오버랩 이벤트 작성하기
	// C++로 캐릭터를 만들었을경우 인벤토리 컴포넌트의 addItem함수를 호출하기
	if (IInventoryPlayerInterface* Player = Cast<IInventoryPlayerInterface>(OtherActor))
	{
		if (Player->AddItem(ItemObject))
		{
			UE_LOG(LogTemp, Warning, TEXT("%s In"), *ItemObject->ItemName.ToString());
			Destroy();
		}
	}
}

void AItemBase::InitializeDrop(UItemObject* ItemToDrop)
{
	ItemObject = ItemToDrop;

	ItemMesh->SetStaticMesh(ItemToDrop->Asset.Mesh);
}

