
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
		for (int j = 0; j < Colums; j++)
		{
			FIntPoint Location(i, j);
			if (IsRoomAvailable(InItem, Location))
			{
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
}

bool UInventoryComponent::IsRoomAvailable(UItemObject* InItem, FIntPoint InLocation)
{
	FIntPoint BottomRight;
	BottomRight.X = InLocation.X + InItem->GetSizeX() - 1;
	BottomRight.Y = InLocation.Y + InItem->GetSizeY() - 1;
	if (IsPositionValid(BottomRight))
	{
		return false;
	}

	return true;
}

bool UInventoryComponent::IsPositionValid(FIntPoint InLocation)
{
	// 아이템을 넣을때 해당 위치가 올바른지 확인
	return InLocation.X >= 0 && InLocation.X < Colums &&
		   InLocation.Y >= 0 && InLocation.Y < Rows;
}

FIntPoint UInventoryComponent::IndexToPoint(int32 TopLeftIndex)
{
	FIntPoint Point;
	Point.X = TopLeftIndex % Colums;
	Point.Y = TopLeftIndex / Colums;
	return Point;
}



