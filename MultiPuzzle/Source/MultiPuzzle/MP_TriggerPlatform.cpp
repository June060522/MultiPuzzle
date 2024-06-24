// Fill out your copyright notice in the Description page of Project Settings.


#include "MP_TriggerPlatform.h"

#include "Components/BoxComponent.h"

#include "MP_MovingPlatform.h"

// Sets default values
AMP_TriggerPlatform::AMP_TriggerPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(FName("TriggerVolume"));
	if (TriggerVolume)
	{
		RootComponent = TriggerVolume;

		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &AMP_TriggerPlatform::OnOverlapBegin);
		TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &AMP_TriggerPlatform::OnOverlapEnd);
	}
}

// Called when the game starts or when spawned
void AMP_TriggerPlatform::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMP_TriggerPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMP_TriggerPlatform::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	for (auto Platform : PlatformsToTrigger)
	{
		Platform->AddActiveTrigger();
	}
}

void AMP_TriggerPlatform::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	for (auto Platform : PlatformsToTrigger)
	{
		Platform->RemoveActiveTrigger();
	}
}

