// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MidnightPowerup_Base.generated.h"

UCLASS()
class MIDNIGHTTASK_API AMidnightPowerup_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	AMidnightPowerup_Base();

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

protected:

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> PickupSound;
};
