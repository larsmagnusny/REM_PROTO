// Fill out your copyright notice in the Description page of Project Settings.

#include "REM_Proto.h"
#include "REM_HUD.h"




AREM_HUD::AREM_HUD()
{
	
}

void AREM_HUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

	MyController->bShowMouseCursor = true;
	MyController->bEnableClickEvents = true;
	MyController->bEnableMouseOverEvents = true;
}

void AREM_HUD::DrawHUD()
{
	Super::DrawHUD();
}