// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SInventoryComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FInventoryChanged);

struct FTile;
class UItemObject;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORY_API USInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UPROPERTY(BlueprintAssignable, Category = "SInventoryComponent")
	FInventoryChanged InventoryChanged;

	USInventoryComponent();

	/*
	* �������� �߰���Ű�� �Լ�
	*/
	bool TryAddItems(UItemObject* InItem);

	/*
	* �������� �κ��丮���� �����ϴ� �Լ�
	*/
	bool RemoveItems(UItemObject* InItem);

	/*
	* ������ ���� �Լ�
	*/
	void EquipItem(UItemObject* InItem);
	/*
	* ������ ���� ���� �Լ�
	*/
	void UnEquipItem(EEquipmentSlotType SlotType);

	/*
	* �������� Drop�Ҷ� ���Ǵ� �Լ�
	*/
	void DropItem(UItemObject* ItemToDrop);

	/*
	* �������� �κ��丮�� �ٸ� �������� �̵���Ű�� �Լ�
	*/
	bool ReplaceItem(UItemObject* ItemToReplace, FIntPoint InLocation);


	/*
	*  �������� ȸ����Ű�� �Լ�
	*/
	void RotateItem(UItemObject* ItemToRotate);
	/*
	* �κ��丮�� �������� ������ ������ �ִ� ������ ���� �ϴ��� Ȯ���ϴ� �Լ�
	*/
	bool IsRoomAvailable(UItemObject* InItem, FIntPoint InLocation);

	UFUNCTION(BlueprintCallable, Category = "SInventoryComponent")
	TArray<UItemObject*> GetInventoryItems() const { return InventoryItems; }

	UFUNCTION(BlueprintCallable, Category = "SInventoryComponent")
	TMap<EEquipmentSlotType, UItemObject*> GetEquipmentItems() const { return EquipmentItems; }
protected:
	virtual void BeginPlay() override;

private:
	// �κ��丮Grid�ʱ�ȭ
	UFUNCTION(BlueprintCallable, Category = "InventoryInit")
	void InitializeInventory();


	/*
	* �������� �������� InventoryGrid�� 1�� �־ ���� ä���
	*/
	void PlaceItem(UItemObject* InItem, FIntPoint InLocation);

	/*
	* �������� �����Ҷ� InventoryGrid������ ������ ������ŭ �ʱ�ȭ ��Ű��
	*/
	void RemovePlaceItem(UItemObject* InItem);

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

	UPROPERTY(VisibleAnywhere, Category = "Equipment", meta = (AllowPrivateAccess = "true"))
	TMap<EEquipmentSlotType, UItemObject*> EquipmentItems;

	UPROPERTY()
	TArray<bool> InventoryGrid;
};