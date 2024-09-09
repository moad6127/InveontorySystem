// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


struct FTile;
class UItemObject;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	bool TryAddItems(UItemObject* InItem);


	TArray<UItemObject*> GetInventoryItems() const { return InventoryItems; }
protected:
	virtual void BeginPlay() override;

private:

	bool IsRoomAvailable(UItemObject* InItem, FIntPoint InLocation);

	bool IsPositionValid(FIntPoint InLocation);

	FIntPoint IndexToPoint(int32 TopLeftIndex);
	void PointToIndex(int32 i, int32 j);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta =(AllowPrivateAccess = "true"))
	int32 Colums = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta = (AllowPrivateAccess = "true"))
	int32 Rows = 5;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Items", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UItemObject>> InventoryItems;
};
