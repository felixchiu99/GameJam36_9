// Fill out your copyright notice in the Description page of Project Settings.


#include "Ai/AiUsable/NpcPatrolPoint.h"

// Sets default values
ANpcPatrolPoint::ANpcPatrolPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANpcPatrolPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANpcPatrolPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
