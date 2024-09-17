// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InventoryWidgetController.h"
#include "InventoryComponent/InventoryComponent.h"
#include "Item/ItemObject.h"

void UInventoryWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	InventoryComponent = WCParams.InventoryComponent;
}

bool UInventoryWidgetController::RemoveItem(UItemObject* InItem)
{
	if (GetInventoryComponent()->RemoveItems(InItem))
	{
		return true;
	}
	return false;
}

void UInventoryWidgetController::DropItem(UItemObject* ItemToDrop)
{
	if (GetInventoryComponent())
	{
		GetInventoryComponent()->DropItem(ItemToDrop);
	}
}

bool UInventoryWidgetController::ReplaceItem(UItemObject* ItemToReplace, FIntPoint InLocation)
{
	if (GetInventoryComponent())
	{
		if (GetInventoryComponent()->ReplaceItem(ItemToReplace, InLocation))
		{
			return true;
		}
	}
	return false;
}
