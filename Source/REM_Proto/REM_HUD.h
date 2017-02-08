// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "REM_HUD.generated.h"

/**
 * 
 */
UCLASS()
class REM_PROTO_API AREM_HUD : public AHUD
{
	GENERATED_BODY()
public:
	AREM_HUD();
	
	virtual void BeginPlay() override;
	virtual void DrawHUD() override;
	
};
