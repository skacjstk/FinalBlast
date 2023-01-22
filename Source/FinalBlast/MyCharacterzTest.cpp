// Fill out your copyright notice in the Description page of Project Settings.


#include "MyCharacterzTest.h"

// Sets default values
AMyCharacterzTest::AMyCharacterzTest()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyCharacterzTest::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyCharacterzTest::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyCharacterzTest::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

