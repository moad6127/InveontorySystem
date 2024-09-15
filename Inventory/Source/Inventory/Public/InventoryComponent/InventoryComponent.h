// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryChanged);

struct FTile;
class UItemObject;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(BlueprintAssignable, Category = "InventoryComponent")
	FInventoryChanged InventoryChanged;

	UInventoryComponent();

	bool TryAddItems(UItemObject* InItem);

	bool RemoveItems(UItemObject* InItem);

	void DropItem(UItemObject* ItemToDrop);

	UFUNCTION(BlueprintCallable, Category = "InventoryComponent")
	TArray<UItemObject*> GetInventoryItems() const { return InventoryItems; }
protected:
	virtual void BeginPlay() override;

private:
	// �κ��丮Grid�ʱ�ȭ
	UFUNCTION(BlueprintCallable, Category = "InventoryInit")
	void InitializeInventory();

	/*
	* �κ��丮�� �������� ������ ������ �ִ� ������ ���� �ϴ��� Ȯ���ϴ� �Լ�
	*/
	bool IsRoomAvailable(UItemObject* InItem, FIntPoint InLocation);
	/*
	* �������� �������� InventoryGrid�� 1�� �־ ���� ä���
	*/
	void PlaceItem(UItemObject* InItem, FIntPoint InLocation);

	/*
	* �������� �����Ҷ� InventoryGrid������ ������ ������ŭ �ʱ�ȭ ��Ű��
	*/
	void RePlaceItem(UItemObject* InItem);

	/*
	* �������� BottomRight�� �κ��丮 ���� ������ �Ѿ���� Ȯ���ϱ�
	*/
	bool IsPositionValid(FIntPoint InLocation);

	FIntPoint IndexToPoint(int32 TopLeftIndex);

	int32 GetIndex(int32 x, int32 y) const { return y * Columns + x; };

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta =(AllowPrivateAccess = "true"))
	int32 Columns = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta = (AllowPrivateAccess = "true"))
	int32 Rows = 5;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category = "Items", meta = (AllowPrivateAccess = "true"))
	TArray<TObjectPtr<UItemObject>> InventoryItems;

	UPROPERTY()
	TArray<bool> InventoryGrid;
};
