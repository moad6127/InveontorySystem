
#include "InventoryComponent/InventoryComponent.h"
#include "Item/ItemObject.h"
#include "InventoryData.h"


UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


bool UInventoryComponent::TryAddItems(UItemObject* InItem)
{
	if (!IsValid(InItem))
	{
		return false;
	}
	return false;
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();

	
}

bool UInventoryComponent::IsRoomAvailable(UItemObject* InItem,const int32 TopLeftIndex)
{
	return false;
}

FTile UInventoryComponent::IndexToTile(const int32 Index) const
{
	FTile Result;
	Result.X = Index % Colums;
	Result.Y = Index / Colums;
	return Result;
}


void UInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

