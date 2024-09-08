// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemBase.h"
#include "Components/SphereComponent.h"
#include "Item/ItemObject.h"
#include "Interface/InventoryPlayerInterface.h"


AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = true;

	ItemMesh = CreateDefaultSubobject<UStaticMeshComponent>("ItemMesh");
	ItemMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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
	ItemObject = NewObject<UItemObject>(this, BaseItem);
	//TODO : ItemValueSet
}

void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// ������ �̺�Ʈ �ۼ��ϱ�
	// C++�� ĳ���͸� ���������� �κ��丮 ������Ʈ�� addItem�Լ��� ȣ���ϱ�
	if (IInventoryPlayerInterface* Player = Cast<IInventoryPlayerInterface>(OtherActor))
	{
		if (Player->AddItem(ItemObject))
		{
			Destroy();
		}
	}
}

