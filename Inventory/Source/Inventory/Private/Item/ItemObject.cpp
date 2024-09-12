// Fill out your copyright notice in the Description page of Project Settings.


#include "Item/ItemObject.h"

UItemObject::UItemObject()
{
}

UItemObject* UItemObject::CreateItemCopy()
{
	UItemObject* ItemCopy = NewObject<UItemObject>(StaticClass());
	ItemCopy->ID = ID;
	ItemCopy->ItemNumbericData = ItemNumbericData;
	ItemCopy->Asset = Asset;
	ItemCopy->ItemName = ItemName;
	ItemCopy->SetItemSizeX(SizeX);
	ItemCopy->SetItemSizeY(SizeY);
	ItemCopy->SetItemItemLocation(ItemLocation);

	return ItemCopy;
}

void UItemObject::SetItemItemLocation(FIntPoint InItemLocation)
{
	ItemLocation = InItemLocation;
}

void UItemObject::SetItemSizeX(int32 InSize)
{
	SizeX = InSize;
}

void UItemObject::SetItemSizeY(int32 InSize)
{
	SizeY = InSize;
}

UTexture2D* UItemObject::GetItemIcon()
{
	if (ItemNumbericData.bIsRotate)
	{
		return Asset.IconRotated;
	}
	return Asset.Icon;
}
