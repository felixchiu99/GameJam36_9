// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CC_Willpower.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THELASTPRESENT_API UCC_Willpower : public UActorComponent
{
	GENERATED_BODY()

	//Willpower counter
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	float Willpower = 0;

	//Max Willpower
	UPROPERTY(EditAnywhere)
	int WillpowerMax = 100;

	//Increment Willpower
	UPROPERTY(EditAnywhere)
	float WillpowerIncrement = 1;

public:	
	// Sets default values for this component's properties
	UCC_Willpower();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void OnUpdate();

	UFUNCTION(BlueprintPure)
	float GetWillpowerPercentage();

	UFUNCTION(BlueprintCallable)
	bool UseWillpower(float used);

};
