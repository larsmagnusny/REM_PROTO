// Fill out your copyright notice in the Description page of Project Settings.

#include "REM_Proto.h"
#include "REM_HUD.h"
#include "Runtime/Engine/Public/Slate/SlateGameResources.h"
#include "Runtime/Engine/Public/ImageUtils.h"

AREM_HUD::AREM_HUD()
{
	if (!ActionBar)
	{
		static ConstructorHelpers::FClassFinder<UUserWidget> ActionBarWidgetClass(TEXT("Class'/Game/Blueprints/Inventory.Inventory_C'"));
		
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

	if (ActionBar)
	{
		ActionBar->AddToViewport();
		ActionBar->GetWidgetFromName(FName("HudReference"));
	}
	// Get the images and set the textures according to what is in the player inventory...

	for (int i = 0; i < 4; i++)
	{
		FString name = "Slot";

		name += FString::FromInt(i);
		UUserWidget* Slot = Cast<UUserWidget>(ActionBar->GetWidgetFromName(FName(*name)));

		UImage* Image = nullptr;

		if (Slot)
			Image = Cast<UImage>(Slot->GetWidgetFromName(FName("Image0")));

		if(Image)
			Slots.Add(Image);
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
		else
		{
			Slots[i]->SetBrush(FSlateBrush());
		}
	}
}

void AREM_HUD::SwapElements(int32 index1, int32 index2)
{
	MainCharacter->SwapInventoryElements(index1, index2);
}