// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "InventoryData.h"
#include "ItemObject.generated.h"

/**
 * 
 */


UCLASS()
class INVENTORY_API UItemObject : public UObject
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Item Data")
	FName ID;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemNumericData ItemNumbericData;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FItemAssetData Asset;

	UPROPERTY(EditAnywhere, Category = "Item Data")
	FText ItemName;

	UItemObject();

	UItemObject* CreateItemCopy();

	FIntPoint GetItemLocation() const { return Location; }
	int32 GetSizeX() const { return SizeX; }
	int32 GetSizeY() const { return SizeY; }
 	void SetItemLocation(FIntPoint InLocation);
	void SetItemSizeX(int32 InSize);
	void SetItemSizeY(int32 InSize);
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
	FIntPoint Location;
};
