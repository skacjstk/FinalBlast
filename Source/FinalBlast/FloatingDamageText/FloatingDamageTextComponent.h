// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "FloatingDamageTextComponent.generated.h"

class AFloatingTextActor;	// 3분쯤에 설명함

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FINALBLAST_API UFloatingDamageTextComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFloatingDamageTextComponent();
protected:
	// FloatingDamageActor 에서 사용할 디스플레이 text
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "FloatingDamageTextComponent", Meta = (AllowPrivateAcess = "true"))	// 5분
	TSubclassOf<AFloatingTextActor>	FloatingTextActorClass = nullptr;

	// 데미지 숫자 간 수직 간격
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "FloatingDamageTextComponent", Meta = (AllowPrivateAcess = "true"))
	float TextVerticalSpacing = 40.0f;

	// 새로운 Text actor가 소환될 때의 오프셋
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "FloatingDamageTextComponent", Meta = (AllowPrivateAcess = "true"))
	float TextVerticalOffset = 100.0f;
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	// Adds the 지정된 text at the 지정된 location in world space
	UFUNCTION(Client, Unreliable, BlueprintCallable, Category = "FloatingDamageTextComponent")	//8~9분쯤 설명: 대충 멀티플레이 게임용인듯
		void AddFloatingText_CLIENT(const FText& text, FVector world_location);
	
private:
	UFUNCTION()
		void OnTextDestroyed(AActor* destroyed_actor);

	// 모든 활성화된 FloatingTextActor 배열
	UPROPERTY()
	TArray< AFloatingTextActor*> ActiveTextActors;
};
