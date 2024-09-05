
#include "InventoryComponent/InventoryComponent.h"
#include "Widget/InventoryWidgetController.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}

UInventoryWidgetController* UInventoryComponent::GetInventoryWidgetController(const FWidgetControllerParams& WCParams)
{
	if (InventoryWidgetController == nullptr)
	{
		InventoryWidgetController = NewObject<UInventoryWidgetController>(this, InventoryWidgetControllerClass);
		InventoryWidgetController->SetWidgetControllerParams(WCParams);
	}
	return InventoryWidgetController;
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

