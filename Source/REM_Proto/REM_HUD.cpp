// Fill out your copyright notice in the Description page of Project Settings.

#include "REM_Proto.h"
#include "REM_HUD.h"
#include "Runtime/Engine/Public/Slate/SlateGameResources.h"
#include "Runtime/Engine/Public/ImageUtils.h"

AREM_HUD::AREM_HUD()
{
	if (!ActionBar)
	{
		static ConstructorHelpers::FClassFinder<UUserWidget> ActionBarWidgetClass(TEXT("WidgetBlueprint'/Game/Meshes/Inventory.Inventory_C'"));
		
		if (ActionBarWidgetClass.Succeeded())
		{
			ActionBarClass = ActionBarWidgetClass.Class;
		}


	}
}

void AREM_HUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* MyController = GetWorld()->GetFirstPlayerController();

	MyController->bShowMouseCursor = true;
	MyController->bEnableClickEvents = true;
	MyController->bEnableMouseOverEvents = true;

	// Create the actionbar widget
	ActionBar = CreateWidget<UUserWidget>(GetWorld()->GetFirstPlayerController(), ActionBarClass);
	ActionBar->AddToViewport();

	// Get the images and set the textures according to what is in the player inventory...

	for (int i = 0; i < 4; i++)
	{
		FString name = "Hotbar";

		name += FString::FromInt(i);

		Slots.Add(Cast<UImage>(ActionBar->GetWidgetFromName(FName(*name))));
	}

	// Get a pointer to the GameMode
	GameMode = Cast<AREM_GameModeBase>(GetWorld()->GetAuthGameMode());
	// Get a pointer to the Character
}

void AREM_HUD::DrawHUD()
{
	Super::DrawHUD();

	if (!MainCharacter)
		MainCharacter = Cast<AMainCharacter>(GameMode->GetMainCharacter());

	for(int32 i = 0; i < Slots.Num(); i++)
	{
		FString tex = MainCharacter->GetInventoryTextureAt(i);

		if (!tex.IsEmpty())
		{
			UTexture2D* Texture = Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *(tex)));
			Slots[i]->SetBrushFromTexture(Texture, true);
		}
	}
}