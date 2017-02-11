// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "REM_GameModeBase.h"
#include "InventoryItem.h"
#include "GameFramework/Character.h"
#include "MainCharacter.generated.h"

UCLASS()
class REM_PROTO_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void KeyboardStartMoveLeft();
	void KeyboardStopMoveLeft();

	void KeyboardStartMoveRight();
	void KeyboardStopMoveRight();

	void KeyboardStartMoveUp();
	void KeyboardStopMoveUp();

	void KeyboardStartMoveDown();
	void KeyboardStopMoveDown();

	void AxisMoveLeftRight(float value);
	void AxisMoveUpDown(float value);

	void MouseLeftClick();
	void MouseRightClick();

	void UpdateMovement();
	void UpdateRotation();

	// Misc functions
	float GetDistanceBetweenActors(AActor* Actor1, AActor* Actor2);

	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	// Inventory functions
	bool AddItemToInventory(InventoryItem* item);

private:
	bool KeyboardMovingLeft = false;
	bool KeyboardMovingRight = false;
	bool KeyboardMovingUp = false;
	bool KeyboardMovingDown = false;

	bool KeyboardControlled = false;
	bool MouseControlled = true;

	float Mass = 0.f;

	UClass* AnimClass;

	USkeletalMeshComponent* SkeletalMeshComponent;

	FRotator Rotation = FRotator(0, 0, 0);

	// MouseMovement
	bool MouseMove = false;
	bool DelayActivate = false;
	UInteractableObject* DelayActivateObject = nullptr;
	AInteractableStaticMeshObject* DelayActivateStaticMeshObject = nullptr;
	FVector MoveTo = FVector(0, 0, 0);

	UStaticMeshComponent* LastComponentMousedOver = nullptr;

	// Pointers to other classes
	AREM_GameModeBase* GameMode = nullptr;

	// Player Inventory
	Inventory* PlayerInventory = nullptr;
};
