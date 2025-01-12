// Fill out your copyright notice in the Description page of Project Settings.


#include "NpcSpawner.h"

// Sets default values
ANpcSpawner::ANpcSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANpcSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANpcSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

