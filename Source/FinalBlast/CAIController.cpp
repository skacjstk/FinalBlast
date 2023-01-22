// Fill out your copyright notice in the Description page of Project Settings.


#include "CAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISenseConfig_Hearing.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Engine.h"

DEFINE_LOG_CATEGORY_STATIC(DeveloperLog, Display, All);

ACAIController::ACAIController()
{
	AIPerceptionComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception"));
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));

	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	DamageConfig = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("Damage Config"));

	SetPerceptionComponent(*AIPerceptionComp);
	// SightConfig
	SightConfig->SightRadius = AISightRadius;
	SightConfig->LoseSightRadius = AILoseSightRadius;
	SightConfig->PeripheralVisionAngleDegrees = AIFieldOfView;
	SightConfig->SetMaxAge(AISightAge);

	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;

	// HearingConfig
	HearingConfig->HearingRange = AIHearingRange;
	HearingConfig->SetMaxAge(AIHearingAge);
	// DamageConfig
	DamageConfig->SetMaxAge(AIDamageAge);

	UE_LOG(DeveloperLog, Display, TEXT("%f"), SightConfig->SightRadius);
	GetPerceptionComponent()->ConfigureSense(*SightConfig);
	GetPerceptionComponent()->ConfigureSense(*HearingConfig);
	GetPerceptionComponent()->ConfigureSense(*DamageConfig);
	GetPerceptionComponent()->SetDominantSense(*DamageConfig->GetSenseImplementation());	// 우선순위

	UE_LOG(DeveloperLog, Display, TEXT("%f"), SightConfig->SightRadius);
	SightConfig->SightRadius = 3000.0f;
	UE_LOG(DeveloperLog, Display, TEXT("%f"), SightConfig->SightRadius);
}

void ACAIController::BeginPlay()
{
	Super::BeginPlay();
//	UE_LOG(DeveloperLog, Display, TEXT("%f"), SightConfig->SightRadius);
}
