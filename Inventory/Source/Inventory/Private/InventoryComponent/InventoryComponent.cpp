
#include "InventoryComponent/InventoryComponent.h"
#include "Item/ItemObject.h"
#include "InventoryData.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


bool UInventoryComponent::TryAddItems(UItemObject* InItem)
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
			FIntPoint Location(i, j);
			if (IsRoomAvailable(InItem, Location))
			{
				//TODO : 인벤토리가 변했기 때문에 UI작업 하기
				PlaceItem(InItem, Location);
				InItem->SetItemLocation(Location);
				InventoryItems.Add(InItem);
			}
		}
	}
	return false;
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();	
	InitializeInventory();
}

void UInventoryComponent::InitializeInventory()
{
	InventoryGrid.Init(false, Columns * Rows);
}

bool UInventoryComponent::IsRoomAvailable(UItemObject* InItem, FIntPoint InLocation)
{
	// BottomRight가 인벤토리 범위를 넘어가는지 확인하기
	FIntPoint BottomRight;
	BottomRight.X = InLocation.X + InItem->GetSizeX() - 1;
	BottomRight.Y = InLocation.Y + InItem->GetSizeY() - 1;
	if (IsPositionValid(BottomRight))
	{
		return false;
	}
	// TopLeft부터 아이템의 사이즈 까지 인벤토리 공간 체크
	// EX) TopLeft가 1,1이고 아이템 Size가 3x3이면
	// BottomRight는 1 + 3 - 1의 값을 가진다.
	for (int i = InLocation.Y; i < InLocation.Y + InItem->GetSizeY() - 1; i++)
	{
		for (int j = InLocation.X; j < InLocation.X + InItem->GetSizeX() - 1; j++)
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

void UInventoryComponent::PlaceItem(UItemObject* InItem, FIntPoint InLocation)
{
	for (int i = InLocation.Y; i < InLocation.Y + InItem->GetSizeY() - 1; i++)
	{
		for (int j = InLocation.X; j < InLocation.X + InItem->GetSizeX() - 1; j++)
		{
			InventoryGrid[GetIndex(j, i)] = true;
		}
	}
}

bool UInventoryComponent::IsPositionValid(FIntPoint InLocation)
{
	// 아이템을 넣을때 해당 위치가 올바른지 확인
	return InLocation.X >= 0 && InLocation.X < Columns &&
		   InLocation.Y >= 0 && InLocation.Y < Rows;
}

FIntPoint UInventoryComponent::IndexToPoint(int32 TopLeftIndex)
{
	FIntPoint Point;
	Point.X = TopLeftIndex % Columns;
	Point.Y = TopLeftIndex / Columns;
	return Point;
}



