// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InventoryWidgetController.h"
#include "InventoryComponent/SInventoryComponent.h"
#include "Item/ItemObject.h"

void UInventoryWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	SInventoryComponent = WCParams.SInventoryComponent;
}

bool UInventoryWidgetController::TryAddItem(UItemObject* InItem)
{
	if (GetSInventoryComponent()->TryAddItems(InItem))
	{
		return true;
	}
	return false;
}

bool UInventoryWidgetController::RemoveItem(UItemObject* InItem)
{
	if (GetSInventoryComponent()->RemoveItems(InItem))
	{
		return true;
	}
	return false;
}

void UInventoryWidgetController::DropItem(UItemObject* ItemToDrop)
{
	if (GetSInventoryComponent())
	{
		GetSInventoryComponent()->DropItem(ItemToDrop);
	}
}

void UInventoryWidgetController::EquipItem(UItemObject* InItem)
{
	if (GetSInventoryComponent())
	{
		GetSInventoryComponent()->EquipItem(InItem);
	}
}

void UInventoryWidgetController::UnEquipItem(UItemObject* ItemToUnEquip)
{
	if (GetSInventoryComponent())
	{
		EEquipmentSlotType SlotType = ItemToUnEquip->SlotType;
		GetSInventoryComponent()->UnEquipItem(SlotType);
	}
}

void UInventoryWidgetController::RotateItem(UItemObject* ItemToRotate)
{
	if (GetSInventoryComponent())
	{
		GetSInventoryComponent()->RotateItem(ItemToRotate);
	}
}

bool UInventoryWidgetController::ReplaceItem(UItemObject* ItemToReplace, FIntPoint InLocation)
{
	if (GetSInventoryComponent())
	{
		if (GetSInventoryComponent()->ReplaceItem(ItemToReplace, InLocation))
		{
			return true;
		}
	}
	return false;
}

bool UInventoryWidgetController::IsRoomAvailable(UItemObject* Payload, FIntPoint Location)
{
	if (GetSInventoryComponent())
	{
		if (GetSInventoryComponent()->IsRoomAvailable(Payload, Location))
		{
			return true;
		}
	}
	return false;
}

void UInventoryWidgetController::MousePositionInTile(const FVector2D MousePosition, bool& Right, bool& Down)
{
	Right = false;
	Down = false;

	float MousePositionX = MousePosition.X;
	float MousePositionY = MousePosition.Y;

	Right = fmod(MousePositionX,TileSize) > (TileSize / 2);
	Down = fmod(MousePositionY, TileSize) > (TileSize / 2);
}
