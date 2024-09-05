// Fill out your copyright notice in the Description page of Project Settings.


#include "Widget/BasicInventoryWidget.h"
#include "Components/UniformGridPanel.h"

void UBasicInventoryWidget::SetWidgetController(UObject* InWidgetController)
{
	WidgetController = InWidgetController;
	WidgetControllerSet();
}
