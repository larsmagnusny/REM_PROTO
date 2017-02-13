// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "Inventory.h"
#include "MainCharacter.h"
#include "Blueprint/UserWidget.h"
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

	UFUNCTION(BlueprintCallable, Category="Cursor Reference")
	void SetCursor(UUserWidget* c)
	{
		Cursor = c;
	}

	UFUNCTION(BlueprintCallable, Category = "Cursor Reference")
	UUserWidget* GetCursorReference()
	{
		return Cursor;
	}

	UFUNCTION(BlueprintCallable, Category = "Get Slot Number")
	void GetSlotNumber(int32& num)
	{
		num = SlotCounter++;
	}

	UFUNCTION(BlueprintCallable, Category = "Swap Inventory Elements")
	void SwapElements(int32 index1, int32 index2);

private:
	UClass* ActionBarClass = nullptr;
	UUserWidget* ActionBar = nullptr;
	TArray<UImage*> Slots;
	AREM_GameModeBase* GameMode = nullptr;
	AMainCharacter* MainCharacter = nullptr;
	UUserWidget* Cursor = nullptr;

	int32 SlotCounter = 0;
};
