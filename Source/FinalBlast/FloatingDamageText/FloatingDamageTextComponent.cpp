// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingDamageTextComponent.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "GameFramework/Pawn.h"
#include "Engine/UserInterfaceSettings.h"
#include "FloatingTextActor.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UFloatingDamageTextComponent::UFloatingDamageTextComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFloatingDamageTextComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFloatingDamageTextComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	const APawn* tempOwner = Cast<APawn>(GetOwner());
	
	if (!IsValid(tempOwner) && tempOwner->IsLocallyControlled() == false)
		return;
	// 뷰포트 사이즈 찾아야 함 ( 스케일에 맞아야 하니까 )

	const FVector2D viewportSize = UWidgetLayoutLibrary::GetViewportSize(this);

	// 값 이상한거 들어오면 return
	if (viewportSize.X <= 0.0f || viewportSize.Y <= 0.0f)
		return;

	// Viewport Scale ( DPI Scale )
	const int32 viewportX = FGenericPlatformMath::FloorToInt(viewportSize.X);
	const int32 viewportY = FGenericPlatformMath::FloorToInt(viewportSize.Y);
	const float viewportScale = GetDefault<UUserInterfaceSettings>(UUserInterfaceSettings::StaticClass())->GetDPIScaleBasedOnSize(FIntPoint(viewportX, viewportY));

	// bad scale 체크
	if (viewportScale <= 0.0f)
		return;

	const APlayerController* tempPlayerController = Cast<APlayerController>(tempOwner->GetController());
	// 플레이어 컨트롤러 없으면 Return
	if (!IsValid(tempPlayerController))
		return;
	// 소유자 플레이어 카메라 위치 정보 반환
	const FVector cameraLocation = tempPlayerController->PlayerCameraManager->GetCameraLocation();
	// 언리얼 4라서 유튜브 강의처럼 즉시 <> 로 캐스팅이 안됨.

	// Adjust(조정하다) location of the active text actors by the vierport size and scale so that they appear evently stacked on the screen
	for (int32 i = 1; i < ActiveTextActors.Num(); ++i) {

		// Calculate the vertical offset based on how fat we (the camera) are from the floating text actor
		AFloatingTextActor* textActor = ActiveTextActors[i];
		const float distance = FVector::Dist(cameraLocation, textActor->GetAnchorLocation());
		const float verticalOffset = distance / (viewportSize.X / viewportScale);

		// Adjust(조정) the floating text actor's location by the calculated amount
		textActor->SetActorLocation(textActor->GetAnchorLocation() + FVector(0.0f, 0.0f, i * verticalOffset * TextVerticalSpacing));
	}
}

// 29분 _Implementation 추가하다가 뭔 설명하면서 지웠음, 그리고 40분 48초에 다시 추가함
void UFloatingDamageTextComponent::AddFloatingText_CLIENT_Implementation(const FText& text, FVector world_location)
{
	if (FloatingTextActorClass == nullptr)
		return;

	// TextActor 소환하고 위치 조정
	const FTransform spawnTransform = FTransform(FRotator::ZeroRotator, world_location + FVector(0.0f, 0.0f, TextVerticalOffset));
	// 31~33분 설명: 우린 Initialize 이벤트를 호출 하고, BeginPlay를 해야 한다: SpawnActor 를 쓰면 너무 늦어지니까
	AFloatingTextActor* newTextActor = GetWorld()->SpawnActorDeferred<AFloatingTextActor>(FloatingTextActorClass, spawnTransform, GetOwner());
	if (newTextActor == nullptr)
		return;

	// Initialize and finish spawning actor
	newTextActor->Initalize(text);
	newTextActor->OnDestroyed.AddDynamic(this, &UFloatingDamageTextComponent::OnTextDestroyed);
	// 이때 BeginPlay가 트리거됨.
	UGameplayStatics::FinishSpawningActor(newTextActor, spawnTransform);

	//Add the new text actor to the beginning of the activeTextActors array
	ActiveTextActors.Insert(newTextActor, 0);
}

void UFloatingDamageTextComponent::OnTextDestroyed(AActor* destroyed_actor)
{
	ActiveTextActors.Pop();

}

