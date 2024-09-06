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

void AInventoryHUD::InitHUD(APlayerController* PC, UInventoryComponent* InventoryComponent)
{
    checkf(InventoryWidgetClass, TEXT("Inventory Widget Class uninitialized, fill out BP_HUD"));
    checkf(InventoryWidgetControllerClass, TEXT("Inventory Widget Controller Class uninitialized, fill out BP_HUD"));

    const FWidgetControllerParams WidgetControllerParmas(PC,InventoryComponent);

    UInventoryWidgetController* WidgetController = GetInventoryWidgetController(WidgetControllerParmas);

    InventoryWidget = CreateWidget<UBasicInventoryWidget>(GetWorld(), InventoryWidgetClass);

    InventoryWidget->SetWidgetController(WidgetController);

    InventoryWidget->AddToViewport();
    InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
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
    }
}

void AInventoryHUD::HideInventory()
{
    if (InventoryWidget)
    {
        bIsInventoryVisible = false;
        InventoryWidget->SetVisibility(ESlateVisibility::Collapsed);
    }
}