// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcCharacter.h"
#include "AIController.h"
#include "Components/ArrowComponent.h"
#include "../PresentPawn.h"

// Sets default values
ANpcCharacter::ANpcCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Preference = ENpcPreference::None;

	HeldPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("HeldPoint"));
	HeldPoint->SetRelativeLocation(FVector(70, 0, 30));
	HeldPoint->SetupAttachment(RootComponent);


}

// Called when the game starts or when spawned
void ANpcCharacter::BeginPlay()
{
	Super::BeginPlay();
	InitPreference();
}

void ANpcCharacter::InitPreference()
{
	int rand = FMath::RandRange(0, 2);
	//Preference = static_cast<ENpcPreference>(rand+1);
	Preference = ENpcPreference::Money;

}

void ANpcCharacter::AttachedPresent()
{
	if (HeldPresent == nullptr) {
		return;
	}

	HeldPresent->SetActorLocation(HeldPoint->GetComponentLocation());
}

// Called every frame
void ANpcCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AttachedPresent();
}

// Called to bind functionality to input
void ANpcCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ANpcCharacter::SetPresent_Implementation(APresentPawn* present)
{
	AAIController* aiController = Cast<AAIController>(this->GetController());
	if (aiController) {
		//UBlackboardComponent* blackboard = aiController->GetBlackboardComponent();
		//blackboard->SetValueAsVector(FName("PointOfInterest"), present->GetLocation());
	}
}

bool ANpcCharacter::PickupPresent_Implementation(APresentPawn* present)
{
	bool canPickUp = !present->IsPickedUp();
	if (canPickUp) {
		HeldPresent = present;
	}
	return canPickUp;
}

bool ANpcCharacter::DropPresent_Implementation()
{
	HeldPresent = nullptr;
	return true;
}

bool ANpcCharacter::CheckPreference(uint8 checkPreference)
{
	bool isSame = checkPreference == (uint8)Preference;
	return isSame;
}

