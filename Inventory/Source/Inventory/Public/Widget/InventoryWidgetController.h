// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryWidgetController.generated.h"

/**
 * 
 */

class USInventoryComponent;
class UItemObject;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()


	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* PC, USInventoryComponent* InvenComp)
		:PlayerController(PC), SInventoryComponent(InvenComp) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USInventoryComponent> SInventoryComponent = nullptr;
};

UCLASS(BlueprintType, Blueprintable)
class INVENTORY_API UInventoryWidgetController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

	UFUNCTION(BlueprintCallable)
	bool TryAddItem(UItemObject* InItem);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(UItemObject* InItem);

	UFUNCTION(BlueprintCallable)
	void DropItem(UItemObject* ItemToDrop);

	UFUNCTION(BlueprintCallable)
	void EquipItem(UItemObject* InItem);
	
	UFUNCTION(BlueprintCallable)
	void UnEquipItem(UItemObject* ItemToUnEquip);

	UFUNCTION(BlueprintCallable)
	void RotateItem(UItemObject* ItemToRotate);

	UFUNCTION(BlueprintCallable)
	bool ReplaceItem(UItemObject* ItemToReplace, FIntPoint InLocation);

	UFUNCTION(BlueprintCallable)
	bool IsRoomAvailable(UItemObject* Payload, FIntPoint Location);

	UFUNCTION(BlueprintCallable)
	void MousePositionInTile(const FVector2D MousePosition, bool& Right, bool& Down);

	UFUNCTION(BlueprintCallable)
	APlayerController* GetPlayerController() { return PlayerController; }

	UFUNCTION(BlueprintCallable)
	USInventoryComponent* GetSInventoryComponent() { return SInventoryComponent; }
protected:

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<USInventoryComponent> SInventoryComponent;

private:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float TileSize = 50.f;

};
