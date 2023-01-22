// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "CAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class FINALBLAST_API UCAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable, Category = "AI|Preception")
		TArray<UAISenseConfig*> GetAiSenseConfigs() { return SensesConfig; }
	//	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "BeginPlay"))
};
