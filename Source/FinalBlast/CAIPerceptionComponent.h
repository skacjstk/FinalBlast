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
		UFUNCTION(BlueprintCallable, meta = (DisplayName = "getconfigs"))
		FORCEINLINE TArray<UAISenseConfig*> GetAiSenseConfigs() { return SensesConfig; }
};
