// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "InventoryHUD.generated.h"

/**
 * 
 */

class UInventoryWidgetController;
class UBasicInventoryWidget;
struct FWidgetControllerParams;
class UInventoryComponent;

UCLASS()
class INVENTORY_API AInventoryHUD : public AHUD
{
	GENERATED_BODY()

public:
	UInventoryWidgetController* GetInventoryWidgetController(const FWidgetControllerParams& WCParams);

	void InitHUD(APlayerController* PC, UInventoryComponent* InventoryComponent);

	void ShowInventory();

protected:

	TObjectPtr<UBasicInventoryWidget> InventoryWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UBasicInventoryWidget>InventoryWidgetClass;

	TObjectPtr<UInventoryWidgetController> InventoryWidgetController;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryWidgetController> InventoryWidgetControllerClass;	

	bool bIsInventoryVisible;

	void DisplayInventory();
	void HideInventory();
};