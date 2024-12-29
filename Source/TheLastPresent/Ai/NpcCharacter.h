// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AiUsable/NpcPreference.h"
#include "NpcCharacter.generated.h"

class APresentPawn;
class UArrowComponent;

UCLASS()
class THELASTPRESENT_API ANpcCharacter : public ACharacter
{
	GENERATED_BODY()

	ENpcPreference Preference;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	APresentPawn* HeldPresent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Gameplay, meta = (AllowPrivateAccess = "true"))
	UArrowComponent* HeldPoint;
public:
	// Sets default values for this character's properties
	ANpcCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void InitPreference();

	void AttachedPresent();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Set present
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetPresent(APresentPawn* present);

	void SetPresent_Implementation(APresentPawn* present);

	// Pickup present
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool PickupPresent(APresentPawn* present);

	bool PickupPresent_Implementation(APresentPawn* present);

	// Drop present
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool DropPresent();

	bool DropPresent_Implementation();

	// Check preference
	UFUNCTION(BlueprintCallable)
	bool CheckPreference(uint8 checkPreference);

};
