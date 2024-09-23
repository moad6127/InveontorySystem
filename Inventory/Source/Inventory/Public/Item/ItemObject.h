// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryData.h"
#include "ItemObject.generated.h"

/**
 * 
 */


UCLASS(BlueprintType, Blueprintable)
class INVENTORY_API UItemObject : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Item Data")
	EEquipmentSlotType SlotType;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemNumericData ItemNumbericData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemAssetData Asset;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FText ItemName;

	UItemObject();

	UItemObject* CreateItemCopy();

	FIntPoint GetItemItemLocation() const { return ItemLocation; }
	int32 GetSizeX() const { return SizeX; }
	int32 GetSizeY() const { return SizeY; };
 	void SetItemItemLocation(FIntPoint InItemLocation);
	void SetItemSizeX(int32 InSize);
	void SetItemSizeY(int32 InSize);

	UFUNCTION(BlueprintCallable)
	FText GetItemName() const { return ItemName; }

	UFUNCTION(BlueprintCallable)
	bool GetRotateState() const { return ItemNumbericData.bIsRotate; }

	void Rotate();

	UFUNCTION(BlueprintCallable)
	UMaterialInstance* GetItemIcon();
protected:

	bool operator==(const FName& OtherID) const
	{
		return ID == OtherID;
	}

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo", meta = (AllowPrivateAccess = "true"))
	int32 SizeX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo", meta = (AllowPrivateAccess = "true"))
	int32 SizeY;

	UPROPERTY(BlueprintReadOnly, Category = "ItemInfo", meta = (AllowPrivateAccess = "true"))
	FIntPoint ItemLocation;
};
