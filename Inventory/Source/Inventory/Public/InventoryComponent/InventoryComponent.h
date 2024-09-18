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

	/*
	* 아이템을 추가시키는 함수
	*/
	bool TryAddItems(UItemObject* InItem);

	/*
	* 아이템을 인벤토리에서 제거하는 함수
	*/
	bool RemoveItems(UItemObject* InItem);

	/*
	* 아이템을 Drop할때 사용되는 함수
	*/
	void DropItem(UItemObject* ItemToDrop);

	/*
	* 아이템을 인벤토리의 다른 공간으로 이동시키는 함수
	*/
	bool ReplaceItem(UItemObject* ItemToReplace, FIntPoint InLocation);


	/*
	*  아이템을 회전시키는 함수
	*/
	void RotateItem(UItemObject* ItemToRotate);
	/*
	* 인벤토리에 아이템을 넣을때 넣을수 있는 공간이 존재 하는지 확인하는 함수
	*/
	bool IsRoomAvailable(UItemObject* InItem, FIntPoint InLocation);

	UFUNCTION(BlueprintCallable, Category = "InventoryComponent")
	TArray<UItemObject*> GetInventoryItems() const { return InventoryItems; }
protected:
	virtual void BeginPlay() override;

private:
	// 인벤토리Grid초기화
	UFUNCTION(BlueprintCallable, Category = "InventoryInit")
	void InitializeInventory();


	/*
	* 아이템이 들어왔을때 InventoryGrid에 1을 넣어서 공간 채우기
	*/
	void PlaceItem(UItemObject* InItem, FIntPoint InLocation);

	/*
	* 아이템을 제거할때 InventoryGrid공간을 아이템 공간만큼 초기화 시키기
	*/
	void RemovePlaceItem(UItemObject* InItem);

	/*
	* 아이템의 BottomRight가 인벤토리 공간 범위를 넘어가는지 확인하기
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
