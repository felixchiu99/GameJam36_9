// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcCharacter.h"
#include "AIController.h"
#include "../PresentPawn.h"

// Sets default values
ANpcCharacter::ANpcCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANpcCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANpcCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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

