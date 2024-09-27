// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS/SInvenFPSCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InventoryComponent/SInventoryComponent.h"
#include "InventoryHUD.h"


ASInvenFPSCharacter::ASInvenFPSCharacter()
{
	SInventoryComponent = CreateDefaultSubobject<USInventoryComponent>("SInventoryComponent");
}

void ASInvenFPSCharacter::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = Cast<APlayerController>(Controller);
	HUD = Cast<AInventoryHUD>(PlayerController->GetHUD());

	if (HUD)
	{
		HUD->InitHUD(PlayerController, SInventoryComponent);
	}
}

void ASInvenFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* PlayerEnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		PlayerEnhancedInputComponent->BindAction(InventoryAction, ETriggerEvent::Completed, this, &ASInvenFPSCharacter::ShowInventory);
	}
}

void ASInvenFPSCharacter::ShowInventory()
{
	if (HUD)
	{
		HUD->ShowInventory();
	}
}



bool ASInvenFPSCharacter::AddItem(UItemObject* InItem)
{
	return SInventoryComponent->TryAddItems(InItem);
}

