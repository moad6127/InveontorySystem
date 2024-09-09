// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ItemObject.generated.h"

/**
 * 
 */


UCLASS()
class INVENTORY_API UItemObject : public UObject
{
	GENERATED_BODY()
public:

	FIntPoint GetItemLocation() const { return Location; }
	int32 GetSizeX() const { return SizeX; }
	int32 GetSizeY() const { return SizeY; }
 	void SetItemLocation(FIntPoint InLocation);
protected:

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo", meta = (AllowPrivateAccess = "true"))
	int32 SizeX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo", meta = (AllowPrivateAccess = "true"))
	int32 SizeY;

	UPROPERTY(BlueprintReadOnly, Category = "ItemInfo", meta = (AllowPrivateAccess = "true"))
	FIntPoint Location;
};
