// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemBase.generated.h"

class USphereComponent;
class UItemObject;
class UDataTable;

UCLASS()
class INVENTORY_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AItemBase();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	virtual void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void InitializeDrop(UItemObject* ItemToDrop);
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UStaticMeshComponent> ItemMesh;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "ItemBase")
	TObjectPtr<UItemObject> ItemObject;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemBase")
	TObjectPtr<UDataTable> ItemDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemBase")
	FName DesiredItemID;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemBase")
	//int32 ItemQuantity;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemBase")
	int32 ItemSizeX;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "ItemBase")
	int32 ItemSizeY;

private:
	void InitializeItem(const TSubclassOf<UItemObject> BaseItem);
};
