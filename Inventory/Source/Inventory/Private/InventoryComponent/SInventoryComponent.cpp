
#include "InventoryComponent/SInventoryComponent.h"
#include "Item/ItemObject.h"
#include "InventoryData.h"
#include "Item/ItemBase.h"


USInventoryComponent::USInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


bool USInventoryComponent::TryAddItems(UItemObject* InItem)
{
	if (!IsValid(InItem))
	{
		return false;
	}
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Columns; j++)
		{
			// TopLeft의 위치에 아이템이 들어올수 있는지 체크하기
			FIntPoint Location(j,i);
			if (IsRoomAvailable(InItem, Location))
			{
				PlaceItem(InItem, Location);
				InItem->SetItemItemLocation(Location);
				InventoryItems.Add(InItem);
				InventoryChanged.Broadcast();
				return true;
			}
		}
	}
	return false;
}

bool USInventoryComponent::RemoveItems(UItemObject* InItem)
{
	if (!IsValid(InItem))
	{
		return false;
	}
	if (InventoryItems.Contains(InItem))
	{
		//TODO : 만약 Stackable아이템이면 아이템 수에서 -1하기
		InventoryItems.Remove(InItem);
		RemovePlaceItem(InItem);
		InventoryChanged.Broadcast();
		return true;
	}
	return false;
}

void USInventoryComponent::EquipItem(UItemObject* InItem)
{
	EEquipmentSlotType ItemSlot = InItem->SlotType;
	if (EquipmentItems.Contains(ItemSlot))
	{
		UnEquipItem(ItemSlot);
	}
	else
	{
		EquipmentItems.Add({ ItemSlot,InItem });
		if (InItem->ItemNumbericData.bExpandableSize)
		{
			Rows += InItem->ItemNumbericData.ExpandableInventorySize;
			InventorySizeChanged.Broadcast();
		}
	}
}

void USInventoryComponent::UnEquipItem(EEquipmentSlotType SlotType)
{
	if (!EquipmentItems.Contains(SlotType))
	{
		UE_LOG(LogTemp, Warning, TEXT("Not have item in EquipmentItems!!"));
		return;
	}
	UItemObject* EquipItem = EquipmentItems[SlotType];
	// Equip창에 Slot을 구분하기위해 Weapon은 1과 2로 나누었다.
	if (SlotType == EEquipmentSlotType::EEST_Weapon1 || SlotType == EEquipmentSlotType::EEST_Weapon2)
	{
		EquipItem->SlotType = EEquipmentSlotType::EEST_Weapon;
	}
	// 제거하는것은 들어온것의 SlotType을 제거한다
	EquipmentItems.Remove(SlotType);
	if (EquipItem->ItemNumbericData.bExpandableSize)
	{
		Rows -= EquipItem->ItemNumbericData.ExpandableInventorySize;
		InventorySizeChanged.Broadcast();
	}
}

void USInventoryComponent::DropItem(UItemObject* ItemToDrop)
{
	// SpawnParasm를 생성한후 설정해주기
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.bNoFail = true;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	//위치를 정해주기 위치는 현재 Component를 가지고 있는 Actor앞의 50정도 위치
	const FVector SpawnLocation{ GetOwner()->GetActorLocation() + (GetOwner()->GetActorForwardVector() * 50.f) };
	const FTransform SpawnTransform(GetOwner()->GetActorRotation(), SpawnLocation);

	AItemBase* DropItem = GetWorld()->SpawnActor<AItemBase>(AItemBase::StaticClass(), SpawnTransform, SpawnParams);

	//Drop아이템에 대해서 Initialize해주기
	DropItem->InitializeDrop(ItemToDrop);
}

bool USInventoryComponent::ReplaceItem(UItemObject* ItemToReplace, FIntPoint InLocation)
{
	if (!IsValid(ItemToReplace))
	{
		return false;
	}
	if (IsRoomAvailable(ItemToReplace, InLocation))
	{
		PlaceItem(ItemToReplace, InLocation);
		ItemToReplace->SetItemItemLocation(InLocation);
		InventoryItems.Add(ItemToReplace);
		InventoryChanged.Broadcast();
		return true;
	}
	return false;
}


void USInventoryComponent::BeginPlay()
{
	Super::BeginPlay();	
	InitializeInventory();
}

void USInventoryComponent::InitializeInventory()
{
	InventoryGrid.Init(false, Columns * Rows);
}

void USInventoryComponent::RotateItem(UItemObject* ItemToRotate)
{
	ItemToRotate->Rotate();
	InventoryChanged.Broadcast();
}

bool USInventoryComponent::IsRoomAvailable(UItemObject* InItem, FIntPoint InLocation)
{
	// BottomRight가 인벤토리 범위를 넘어가는지 확인하기
	
	int32 BottomRightX = InLocation.X + InItem->GetSizeX();
	int32 BottomRightY = InLocation.Y + InItem->GetSizeY();
	FIntPoint BottomRight(BottomRightX, BottomRightY);
	if (!IsPositionValid(InLocation))
	{
		return false;
	}
	if (!IsPositionValid(BottomRight))
	{
		return false;
	}
	// TopLeft부터 아이템의 사이즈 까지 인벤토리 공간 체크
	// EX) TopLeft가 1,1이고 아이템 Size가 3x3이면
	// BottomRight는 1 + 3의 값을 가진다.
	for (int32 i = InLocation.Y; i < InLocation.Y + InItem->GetSizeY(); i++)
	{
		for (int32 j = InLocation.X; j < InLocation.X + InItem->GetSizeX(); j++)
		{
			//인벤토리를 순회하면서 TopLeft부터 BottomRight까지 인벤토리Grid를 확인해서
			// Grid가 1일경우 false반환하기
			if (InventoryGrid[GetIndex(j,i)])
			{
				return false;
			}
		}
	}

	return true;
}

void USInventoryComponent::PlaceItem(UItemObject* InItem, FIntPoint InLocation)
{
	for (int32 i = InLocation.Y; i < InLocation.Y + InItem->GetSizeY(); i++)
	{
		for (int32 j = InLocation.X; j < InLocation.X + InItem->GetSizeX(); j++)
		{
			InventoryGrid[GetIndex(j, i)] = true;
		}
	}
}

void USInventoryComponent::RemovePlaceItem(UItemObject* InItem)
{
	FIntPoint InLocation = InItem->GetItemItemLocation();
	for (int32 i = InLocation.Y; i < InLocation.Y + InItem->GetSizeY(); i++)
	{
		for (int32 j = InLocation.X; j < InLocation.X + InItem->GetSizeX(); j++)
		{
			InventoryGrid[GetIndex(j, i)] = false;
		}
	}
}

bool USInventoryComponent::IsPositionValid(FIntPoint InLocation)
{
	// 아이템을 넣을때 해당 위치가 올바른지 확인
	return InLocation.X >= 0 && InLocation.X <= Columns && InLocation.Y >= 0 && InLocation.Y <= Rows;
}

FIntPoint USInventoryComponent::IndexToPoint(int32 TopLeftIndex)
{
	FIntPoint Point;
	Point.X = TopLeftIndex % Columns;
	Point.Y = TopLeftIndex / Columns;
	return Point;
}



