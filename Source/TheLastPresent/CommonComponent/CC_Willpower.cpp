// Fill out your copyright notice in the Description page of Project Settings.


#include "CC_Willpower.h"

// Sets default values for this component's properties
UCC_Willpower::UCC_Willpower()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UCC_Willpower::BeginPlay()
{
	Super::BeginPlay();

	Willpower = WillpowerMax;
	
}


// Called every frame
void UCC_Willpower::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCC_Willpower::OnUpdate()
{
	Willpower += WillpowerIncrement;
	if (Willpower > WillpowerMax) {
		Willpower = WillpowerMax;
	}
}

float UCC_Willpower::GetWillpowerPercentage()
{
	float percentage = (Willpower / WillpowerMax);
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::SanitizeFloat(percentage));

	return percentage;
}

bool UCC_Willpower::UseWillpower(float used)
{
	if (Willpower < used) {
		return false;
	}
	Willpower -= used;
	return true;
}

