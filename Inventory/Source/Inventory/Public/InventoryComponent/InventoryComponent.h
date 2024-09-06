// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"


class UInventoryWidgetController;
struct FWidgetControllerParams;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class INVENTORY_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	UInventoryWidgetController* GetInventoryWidgetController(const FWidgetControllerParams& WCParams);
protected:
	virtual void BeginPlay() override;

private:

	TObjectPtr<UInventoryWidgetController> InventoryWidgetController;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryWidgetController> InventoryWidgetControllerClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta =(AllowPrivateAccess = "true"))
	int32 Colums = 5;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Constants", meta = (AllowPrivateAccess = "true"))
	int32 Rows = 5;
};
