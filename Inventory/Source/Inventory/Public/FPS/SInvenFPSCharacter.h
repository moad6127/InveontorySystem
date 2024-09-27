// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPSCharacter.h"
#include "Interface/InventoryPlayerInterface.h"
#include "SInvenFPSCharacter.generated.h"

/**
 * 
 */

class AInventoryHUD;
class USInventoryComponent;

UCLASS()
class INVENTORY_API ASInvenFPSCharacter : public AFPSCharacter, public IInventoryPlayerInterface
{
	GENERATED_BODY()

	virtual bool AddItem(UItemObject* InItem) override;

protected:

	ASInvenFPSCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Inventory, meta = (AllowPrivateAccess = "true"))
	USInventoryComponent* SInventoryComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* InventoryAction;

	UPROPERTY()
	AInventoryHUD* HUD;

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void ShowInventory();
};
