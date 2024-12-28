// Fill out your copyright notice in the Description page of Project Settings.


#include "PresentPawn.h"
#include "Camera/CameraComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
//Custom scripts
#include "CommonComponent/CC_Willpower.h"

// Sets default values
APresentPawn::APresentPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	PresentMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PresentMesh"));
	PresentMesh->SetupAttachment(RootComponent);

	RootComponent = PresentMesh;

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	
	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create Willpower component
	Willpower = CreateDefaultSubobject<UCC_Willpower>(TEXT("Willpower"));
}

void APresentPawn::Look(const FInputActionValue& Value)
{
	if (!bLookToogle)
		return;
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void APresentPawn::Jump()
{
	bool canMove = true;
	int willpowerUsed = WillpowerMove;
	canMove &= Willpower->UseWillpower(WillpowerJump);

	if (!canMove) {
		return;
	}

	PresentMesh->AddImpulse(  FVector(0, 0, 1) * 50000 );
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("jump"));
	//bPressedJump = true;
	//JumpKeyHoldTime = 0.0f;
}

void APresentPawn::StopJumping()
{
	//bPressedJump = false;
	ResetJumpState();
}

void APresentPawn::Move()
{
	if (bLookToogle)
		return;
	APlayerController* PlayerController = GetLocalViewingPlayerController();
	FVector MouseWorldPosition;
	FVector MouseWorldDirection;
	PlayerController->DeprojectMousePositionToWorld(MouseWorldPosition, MouseWorldDirection);

	FHitResult HitResult;
	if (PlayerController->GetHitResultUnderCursor(ECC_Visibility, true, HitResult))
	{
		FVector impactPoint = HitResult.ImpactPoint;

		bool canMove = true;
		int willpowerUsed = WillpowerMove;
		canMove &= Willpower->UseWillpower(willpowerUsed);

		if (!canMove) {
			return;
		}

		//PresentMesh->AddImpulse( ( impactPoint - this->GetActorLocation()).GetSafeNormal() + FVector(0, 0, 0.5) * 100000);
		PresentMesh->AddImpulseAtLocation((impactPoint - this->GetActorLocation()).GetSafeNormal() * 100000 + FVector(0, 0, 0.5f), GetActorLocation() + FVector(0, 0, 0.6f));
	}

	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("Clicked"));
}

void APresentPawn::LookPressed()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("lookPressed"));
	if (bLookToogle)
		return;
	bLookToogle = true;
	APlayerController* PC = Cast<APlayerController>(GetController());

	if (PC)
	{
		PC->bShowMouseCursor = false;
		PC->bEnableClickEvents = false;
		PC->bEnableMouseOverEvents = false;
	}
}

void APresentPawn::LookPressedEnded()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("lookPressedEnded"));
	bLookToogle = false;
	APlayerController* PC = Cast<APlayerController>(GetController());

	if (PC)
	{
		PC->bShowMouseCursor = true;
		PC->bEnableClickEvents = true;
		PC->bEnableMouseOverEvents = true;
	}
}

void APresentPawn::ResetJumpState()
{
	/*
	bPressedJump = false;
	bWasJumping = false;
	JumpKeyHoldTime = 0.0f;
	JumpForceTimeRemaining = 0.0f;

	if (CharacterMovement && !CharacterMovement->IsFalling())
	{
		JumpCurrentCount = 0;
		JumpCurrentCountPreJump = 0;
	}
	*/
}

// Called to bind functionality to input
void APresentPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {

		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &APresentPawn::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &APresentPawn::StopJumping);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &APresentPawn::Look);

		// Looking Pressed
		EnhancedInputComponent->BindAction(LookPressedAction, ETriggerEvent::Started, this, &APresentPawn::LookPressed);
		EnhancedInputComponent->BindAction(LookPressedAction, ETriggerEvent::Completed, this, &APresentPawn::LookPressedEnded);

		// Clicking
		EnhancedInputComponent->BindAction(ClickAction, ETriggerEvent::Triggered, this, &APresentPawn::Move);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}

// Called when the game starts or when spawned
void APresentPawn::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	GetWorld()->GetTimerManager().SetTimer(UpdateTimer, this, &APresentPawn::OnTimerUpdate, 0.1f, true);
}

void APresentPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	// It's important to keep the call chain on EndPlay or you may end up with serious bugs or crashes
	Super::EndPlay(EndPlayReason);

	// There's a chance your timer is still running when our Actor is destroyed
	// So we need to make sure we clear the timer on EndPlay just in case.
	// This is safe to call even if the timer handle's already been cleared.
	GetWorld()->GetTimerManager().ClearTimer(UpdateTimer);
}

void APresentPawn::OnTimerUpdate()
{
	Willpower->OnUpdate();
}

// Called every frame
void APresentPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
