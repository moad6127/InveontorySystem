// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryWidgetController.generated.h"

/**
 * 
 */

class UInventoryComponent;


USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()


	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* PC, UInventoryComponent* InvenComp)
		:PlayerController(PC), InventoryComponent(InvenComp) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UInventoryComponent> InventoryComponent = nullptr;
};

UCLASS(BlueprintType, Blueprintable)
class INVENTORY_API UInventoryWidgetController : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

	UFUNCTION(BlueprintCallable)
	APlayerController* GetPlayerController() { return PlayerController; }

	UFUNCTION(BlueprintCallable)
	UInventoryComponent* GetInventoryComponent() { return InventoryComponent; }
protected:

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "WidgetController")
	TObjectPtr<UInventoryComponent> InventoryComponent;

private:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float TileSize = 50.f;

};
