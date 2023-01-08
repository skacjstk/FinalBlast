// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FloatingTextActor.generated.h"

UCLASS(Abstract)
class FINALBLAST_API AFloatingTextActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFloatingTextActor();

	// Initializes the actor with required staring information
	UFUNCTION(BlueprintImplementableEvent, Category = "FloatingTextActor")
		void Initalize(const FText& text);

	// Gets the anchor Location
	inline const FVector& GetAnchorLocation() const { return AnchorLocation; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;



private:
	// The location to which the text is anchored: Text가 앵커된 위치
	FVector AnchorLocation;

};
