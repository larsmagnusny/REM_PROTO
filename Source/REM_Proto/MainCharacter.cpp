// Fill out your copyright notice in the Description page of Project Settings.

#include "REM_Proto.h"
#include "MainCharacter.h"
#include "AI/Navigation/NavigationSystem.h"
#include "InteractableObject.h"


// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->bAbsoluteRotation = true; // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 1500.f;
	CameraBoom->RelativeRotation = FRotator(-60.f, 0.f, 0.f);
	CameraBoom->bDoCollisionTest = true; // Don't want to pull camera in when it collides with level

										  // Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	// Switch to the cameracomponent attached to this player
	GetWorld()->GetFirstPlayerController()->SetViewTarget(this);	
	SetupPlayerInputComponent(GetWorld()->GetFirstPlayerController()->InputComponent);

	SkeletalMeshComponent = Cast<USkeletalMeshComponent>(GetComponentByClass(USkeletalMeshComponent::StaticClass()));

	// Get a pointer to the gamemodeclass so we can set the camera and do other things later
	GameMode = Cast<AREM_GameModeBase>(GetWorld()->GetAuthGameMode());
	GameMode->SetMainCamera(TopDownCameraComponent);
	
	// Initialize Inventory
	PlayerInventory = new Inventory();

	// Make the game mode aware that we exist
	UE_LOG(LogTemp, Error, TEXT("Main Character set!"));
	GameMode->SetMainCharacter(this);
}

// Called every frame
void AMainCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	// Keyboard controlled character
	if (KeyboardControlled)
	{
		UpdateRotation();
		UpdateMovement();
	}

	// Mouse Controlled character
	if (MouseControlled)
	{
		// Raycast under the mouse so we can highlight the objects
		FHitResult Hit;
		GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false, Hit);

		// If we hit an actor
		if (Hit.GetActor())
		{
			// If the actor is a AStaticMeshActor
			if (Hit.GetActor()->IsA(AStaticMeshActor::StaticClass()))
			{
				// Get a pointer to the actor and MeshComponent
				AStaticMeshActor* OurActor = Cast<AStaticMeshActor>(Hit.GetActor());
				UStaticMeshComponent* MeshComponent = Cast<UStaticMeshComponent>(OurActor->GetComponentByClass(UStaticMeshComponent::StaticClass()));
				
				// Check if didn't already highligh it last frame
				if (MeshComponent != LastComponentMousedOver)
				{
					// If it has not been set dont do anything
					if (LastComponentMousedOver)
						LastComponentMousedOver->SetRenderCustomDepth(false);
				}

				// Tell the gamemodeclass to check if this actor is interactable
				if (GameMode->IsInteractible(Hit.GetActor()))
				{
					// If it is, set a highlight over it
					MeshComponent->SetRenderCustomDepth(true);

					// Remember this for the next frame
					LastComponentMousedOver = MeshComponent;
				}
			}
		}
		else {
			// If we are not mousing over an interactable object
			if (LastComponentMousedOver)
				LastComponentMousedOver->SetRenderCustomDepth(false);
			LastComponentMousedOver = nullptr;
		}

		// If the player has clicked somewhere on the screen to move
		if (MouseMove)
		{
			// Get a pointer to the built in navigation system in Unreal 4
			UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();

			// Get the distance to the destination
			float const Distance = FVector::Dist(MoveTo, GetActorLocation());

			// If we are not within 80 cm of the destination we should move towards it 
			if (NavSys && (Distance > 80.0f))
			{
				NavSys->SimpleMoveToLocation(Controller, MoveTo);
			}
			else {
				// If we are at the destination
				MouseMove = false;

				// Activate the object if we clicked on an interactable object earlier
				if (DelayActivate)
				{
					UE_LOG(LogTemp, Warning, TEXT("Got interactor, sending activate command..."));
					if (DelayActivateObject)
					{
						DelayActivateObject->ActivateObject();
						DelayActivateObject = nullptr;
					}
					if (DelayActivateStaticMeshObject)
					{
						DelayActivateStaticMeshObject->ActivateObject(Cast<AActor>(this));
						DelayActivateStaticMeshObject = nullptr;
					}
					DelayActivate = false;
				}
			}
		}
	}
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(FName("Left"), EInputEvent::IE_Pressed, this, &AMainCharacter::KeyboardStartMoveLeft);
	PlayerInputComponent->BindAction(FName("Left"), EInputEvent::IE_Released, this, &AMainCharacter::KeyboardStopMoveLeft);

	PlayerInputComponent->BindAction(FName("Right"), EInputEvent::IE_Pressed, this, &AMainCharacter::KeyboardStartMoveRight);
	PlayerInputComponent->BindAction(FName("Right"), EInputEvent::IE_Released, this, &AMainCharacter::KeyboardStopMoveRight);

	PlayerInputComponent->BindAction(FName("Up"), EInputEvent::IE_Pressed, this, &AMainCharacter::KeyboardStartMoveUp);
	PlayerInputComponent->BindAction(FName("Up"), EInputEvent::IE_Released, this, &AMainCharacter::KeyboardStopMoveUp);

	PlayerInputComponent->BindAction(FName("Down"), EInputEvent::IE_Pressed, this, &AMainCharacter::KeyboardStartMoveDown);
	PlayerInputComponent->BindAction(FName("Down"), EInputEvent::IE_Released, this, &AMainCharacter::KeyboardStopMoveDown);

	PlayerInputComponent->BindAxis(FName("AxisLeftRight"), this, &AMainCharacter::AxisMoveLeftRight);
	PlayerInputComponent->BindAxis(FName("AxisUpDown"), this, &AMainCharacter::AxisMoveUpDown);

	PlayerInputComponent->BindAction(FName("MouseClickLeft"), EInputEvent::IE_Pressed, this, &AMainCharacter::MouseLeftClick);
	PlayerInputComponent->BindAction(FName("MouseClickRight"), EInputEvent::IE_Pressed, this, &AMainCharacter::MouseRightClick);
}

void AMainCharacter::KeyboardStartMoveLeft()
{
	KeyboardMovingLeft = true;
}
void AMainCharacter::KeyboardStopMoveLeft()
{
	KeyboardMovingLeft = false;
}

void AMainCharacter::KeyboardStartMoveRight()
{
	KeyboardMovingRight = true;
}
void AMainCharacter::KeyboardStopMoveRight()
{
	KeyboardMovingRight = false;
}

void AMainCharacter::KeyboardStartMoveUp()
{
	KeyboardMovingUp = true;
}
void AMainCharacter::KeyboardStopMoveUp()
{
	KeyboardMovingUp = false;
}

void AMainCharacter::KeyboardStartMoveDown()
{
	KeyboardMovingDown = true;
}
void AMainCharacter::KeyboardStopMoveDown()
{
	KeyboardMovingDown = false;
}

void AMainCharacter::AxisMoveLeftRight(float value)
{
	// Implement later
}
void AMainCharacter::AxisMoveUpDown(float value)
{
	// Implement later
}

void AMainCharacter::MouseLeftClick()
{
	// If the player has left clicked we should raycast under the mouse
	if (!CanClickRaycast)
		return;

	FHitResult Hit;

	GetWorld()->GetFirstPlayerController()->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), false, Hit);

	AActor* HitActor = Hit.GetActor();

	// if the player hit an object
	if (HitActor)
	{
		// Check if the object is interactable
		if (GameMode->IsInteractible(HitActor))
		{
			// Get the instance pointer to the Interactor from the gamemode where we keep track of all interactable items
			UInteractableObject* Component = GameMode->GetInteractor(HitActor);

			// If it is not a nullptr
			if (Component)
			{
				// Check how close we are to it
				if (GetDistanceBetweenActors(HitActor, this) > 100)
				{
					UE_LOG(LogTemp, Warning, TEXT("Not close enough to activate, moving to it..."));
					DelayActivate = true;
					DelayActivateObject = Component;
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("Got interactor, sending activate command..."));
					Component->ActivateObject();
				}
			}
			else {
				// If the interactor does not exist that means we still have to check if the AInteractableStaticMeshObject exists for that object
				UE_LOG(LogTemp, Warning, TEXT("Can't find interactor checking if it actually is a StaticMeshInteractor"));

				AInteractableStaticMeshObject* StaticMeshInteractor = GameMode->GetStaticMeshInteractor(HitActor);

				// If it exists do the same thing as above
				if (StaticMeshInteractor)
				{
					if (GetDistanceBetweenActors(HitActor, this) > 100)
					{
						UE_LOG(LogTemp, Warning, TEXT("Not close enough to pick up object, moving to it..."));
						DelayActivate = true;
						DelayActivateStaticMeshObject = StaticMeshInteractor;
					}
					else {
						UE_LOG(LogTemp, Warning, TEXT("Got StaticMeshInteractor, sending activate command..."));
						StaticMeshInteractor->ActivateObject(Cast<AActor>(this));
					}
				}
			}
		}

		MoveTo = Hit.ImpactPoint;
		MouseMove = true;
	}
}
void AMainCharacter::MouseRightClick()
{

}

void AMainCharacter::UpdateMovement()
{
	if (KeyboardMovingLeft)
	{
		AddMovementInput(FVector(1, 0, 0), 1.0f);
	}

	if (KeyboardMovingRight)
	{
		AddMovementInput(FVector(-1, 0, 0), 1.0f);
	}

	if (KeyboardMovingUp)
	{
		AddMovementInput(FVector(0, 1, 0), 1.0f);
	}

	if (KeyboardMovingDown)
	{
		AddMovementInput(FVector(0, -1, 0), 1.0f);
	}
}

void AMainCharacter::UpdateRotation()
{
	if (!SkeletalMeshComponent)
		return;

	if (KeyboardMovingLeft && !KeyboardMovingRight)
	{
		Rotation = FRotator(0, -90, 0);
	}

	if (KeyboardMovingRight && !KeyboardMovingLeft)
	{
		Rotation = FRotator(0, 90, 0);
	}

	if (KeyboardMovingUp && !KeyboardMovingDown)
	{
		Rotation = FRotator(0, 0, 0);
	}

	if (KeyboardMovingDown && !KeyboardMovingUp)
	{
		Rotation = FRotator(0, 180, 0);
	}

	if (KeyboardMovingLeft && KeyboardMovingUp)
	{
		Rotation = FRotator(0, -45, 0);
	}

	if (KeyboardMovingRight && KeyboardMovingUp)
	{
		Rotation = FRotator(0, 45, 0);
	}

	if (KeyboardMovingLeft && KeyboardMovingDown)
	{
		Rotation = FRotator(0, -135, 0);
	}

	if (KeyboardMovingRight && KeyboardMovingDown)
	{
		Rotation = FRotator(0, 135, 0);
	}

	SkeletalMeshComponent->SetWorldRotation(Rotation);
}

// Misc functions
float AMainCharacter::GetDistanceBetweenActors(AActor* Actor1, AActor* Actor2)
{
	return FVector::Dist(Actor1->GetActorLocation(), Actor2->GetActorLocation());
}

// Adds items to the inventory
bool AMainCharacter::AddItemToInventory(InventoryItem* item)
{
	if (PlayerInventory)
		return PlayerInventory->AddItem(item);
	else
		return false;
}

// Gets the inventory array
FString AMainCharacter::GetInventoryTextureAt(int index)
{
	return PlayerInventory->GetTextureAt(index);
}

int AMainCharacter::GetInventorySize()
{
	return PlayerInventory->GetSize();
}

void AMainCharacter::SwapInventoryElements(int32 index1, int32 index2)
{
	PlayerInventory->Swap(index1, index2);
}

void AMainCharacter::DropItem(int32 slotindex, FVector2D EndPoint)
{
	GameMode->PutObjectInWorld(PlayerInventory->GetItem(slotindex), EndPoint);
}

void AMainCharacter::DiscardItem(InventoryItem* item)
{
	PlayerInventory->DiscardItem(item);
}