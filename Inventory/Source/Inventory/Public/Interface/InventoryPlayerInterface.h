// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InventoryPlayerInterface.generated.h"

class UItemObject;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInventoryPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class INVENTORY_API IInventoryPlayerInterface
{
	GENERATED_BODY()

public:
	virtual bool AddItem(UItemObject* InItem);

};
