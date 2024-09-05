// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/InventoryWidgetController.h"

void UInventoryWidgetController::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	InventoryComponent = WCParams.InventoryComponent;
}
