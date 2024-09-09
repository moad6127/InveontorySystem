
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
			// TopLeft�� ��ġ�� �������� ���ü� �ִ��� üũ�ϱ�
			FIntPoint Location(i, j);
			if (IsRoomAvailable(InItem, Location))
			{
				//TODO : �κ��丮�� ���߱� ������ UI�۾� �ϱ�
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
	// BottomRight�� �κ��丮 ������ �Ѿ���� Ȯ���ϱ�
	FIntPoint BottomRight;
	BottomRight.X = InLocation.X + InItem->GetSizeX() - 1;
	BottomRight.Y = InLocation.Y + InItem->GetSizeY() - 1;
	if (IsPositionValid(BottomRight))
	{
		return false;
	}
	// TopLeft���� �������� ������ ���� �κ��丮 ���� üũ
	// EX) TopLeft�� 1,1�̰� ������ Size�� 3x3�̸�
	// BottomRight�� 1 + 3 - 1�� ���� ������.
	for (int i = InLocation.Y; i < InLocation.Y + InItem->GetSizeY() - 1; i++)
	{
		for (int j = InLocation.X; j < InLocation.X + InItem->GetSizeX() - 1; j++)
		{
			//�κ��丮�� ��ȸ�ϸ鼭 TopLeft���� BottomRight���� �ٸ� �������� �����ϸ� 
			//False�� ��ȯ
			for (UItemObject* Item : InventoryItems)
			{
				if (Item->GetItemLocation() == FIntPoint(i, j))
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool UInventoryComponent::IsPositionValid(FIntPoint InLocation)
{
	// �������� ������ �ش� ��ġ�� �ùٸ��� Ȯ��
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



