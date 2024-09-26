// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BasicInventoryWidget.generated.h"

/**
 * 
 */

class UUniformGridPanel;
class USInventoryComponent;

UCLASS()
class INVENTORY_API UBasicInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//~ Function
	UFUNCTION(BlueprintCallable)
	void SetWidgetController(UObject* InWidgetController);
	//~ Function

	//~ Value
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UObject> WidgetController;
	//~ Value

protected:
	UFUNCTION(BlueprintImplementableEvent)
	void WidgetControllerSet();

private:


};
