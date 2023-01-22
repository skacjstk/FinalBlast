// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CAIController.generated.h"

/**
 * 
 */
UCLASS()
class FINALBLAST_API ACAIController : public AAIController
{
	GENERATED_BODY()

public:
	ACAIController();

	virtual void BeginPlay() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAISenseConfig_Sight* SightConfig;

//	UPROPERTY(EditAnywhere, BlueprintReadWrite)
//		class UAISenseConfig_Sight* SightConfig2;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAISenseConfig_Hearing* HearingConfig;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UAISenseConfig_Damage* DamageConfig;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		class UAIPerceptionComponent* AIPerceptionComp;

private:
	// Sight
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SightConfig", meta = (AllowPrivateAccess = true))
		float AISightRadius = 1000.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SightConfig", meta = (AllowPrivateAccess = true))
		float AILoseSightRadius = AISightRadius + 200.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SightConfig", meta = (AllowPrivateAccess = true))
		float AIFieldOfView = 80.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "SightConfig", meta = (AllowPrivateAccess = true))
		float AISightAge = 2.0f;

	// Hearing
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HearingConfig", meta = (AllowPrivateAccess = true))
		float AIHearingRange = 3500.0f;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "HearingConfig", meta = (AllowPrivateAccess = true))
		float AIHearingAge = 1.0f;

	// Damage
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "DamageConfig", meta = (AllowPrivateAccess = true))
		float AIDamageAge = 15.0f;

public:	// 메소드
	UFUNCTION(BlueprintCallable)
		class UAISenseConfig_Sight* GetCurrentAISightConfig() { return SightConfig; }
	UFUNCTION(BlueprintCallable)
		class UAISenseConfig_Hearing* GetCurrentAIHearingConfig() { return HearingConfig; }
	UFUNCTION(BlueprintCallable)
		class UAISenseConfig_Damage* GetCurrentAIDamageConfig() { return DamageConfig; }

	UFUNCTION(BlueprintCallable)
		void SetAISightRadius(float sightRadius) { AISightRadius = sightRadius; }
};
