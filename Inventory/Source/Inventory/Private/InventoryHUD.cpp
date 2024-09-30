// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryHUD.h"
#include "Widget/InventoryWidgetController.h"
#include "Widget/BasicInventoryWidget.h"

UInventoryWidgetController* AInventoryHUD::GetInventoryWidgetController(const FWidgetControllerParams& WCParams)
{
    if (InventoryWidgetController == nullptr)
    {
        InventoryWidgetController = NewObject<UInventoryWidgetController>(this, InventoryWidgetControllerClass);
        InventoryWidgetController->SetWidgetControllerParams(WCParams);
    }
    return InventoryWidgetController;
}

void AInventoryHUD::InitHUD(APlayerController* PC, USInventoryComponent* SInventoryComponent)
{
    checkf(InventoryWidgetClass, TEXT("Inventory Widget Class uninitialized, fill out BP_HUD"));
    checkf(InventoryWidgetControllerClass, TEXT("Inventory Widget Controller Class uninitialized, fill out BP_HUD"));

    const FWidgetControllerParams WidgetControllerParmas(PC,SInventoryComponent);

    UInventoryWidgetController* WidgetController = GetInventoryWidgetController(WidgetControllerParmas);

    InventoryWidget = CreateWidget<UBasicInventoryWidget>(GetWorld(), InventoryWidgetClass);
    HUDWidget = CreateWidget<UBasicInventoryWidget>(GetWorld(), HUDWidgetClass);

    InventoryWidget->SetWidgetController(WidgetController);
    HUDWidget->SetWidgetController(WidgetController);

    InventoryWidget->AddToViewport();
    HUDWidget->AddToViewport();

    InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
    bIsInventoryVisible = false;
}

void AInventoryHUD::ShowInventory()
{
    if (bIsInventoryVisible)
    {
        HideInventory();
    }
    else
    {
        DisplayInventory();
    }
}

void AInventoryHUD::DisplayInventory()
{
    if (InventoryWidget)
    {
        bIsInventoryVisible = true;
        InventoryWidget->SetVisibility(ESlateVisibility::Visible);
        const FInputModeGameAndUI InputMode;
        GetOwningPlayerController()->SetInputMode(InputMode);
        GetOwningPlayerController()->SetShowMouseCursor(true);
    }
}

void AInventoryHUD::HideInventory()
{
    if (InventoryWidget)
    {
        bIsInventoryVisible = false;
        InventoryWidget->SetVisibility(ESlateVisibility::Hidden);
        const FInputModeGameOnly InputMode;
        GetOwningPlayerController()->SetInputMode(InputMode);
        GetOwningPlayerController()->SetShowMouseCursor(false);
    }
}
