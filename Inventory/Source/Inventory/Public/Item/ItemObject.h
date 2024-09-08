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

	FIntPoint GetDimensions() const { return Dimensions; }
protected:

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemInfo", meta = (AllowPrivateAccess = "true"))
	FIntPoint Dimensions;
};
