// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "GameFramework/GameModeBase.h"
#include "MidnigthGameModeBase.generated.h"


class AMidnightDoor;
class AMidnightPowerup_Base;
class UEnvQuery;
class UEnvQueryInstanceBlueprintWrapper;

UCLASS()
class MIDNIGHTTASK_API AMidnigthGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	virtual void StartPlay() override;

	void AddPlayerPicked();
	
protected:

	FTimerHandle TimerHandle_SpawnPickups;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	UEnvQuery* SpawnPickupsQuery = nullptr;
	
	UPROPERTY(EditDefaultsOnly, Category = "Pickups")
	float SpawnPickupsTimerInterval = 2.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Pickups")
	int32 MaxPickupsCount = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Pickups")
	uint32 PlayerPickedGoal = 5;
	
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	TArray<TSubclassOf<AMidnightPowerup_Base>> PickupClasses;

	UFUNCTION()
	void OnPickupSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus);

	void SpawnPickupsTimerElapsed();

	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<AMidnightDoor> DoorToOpen;
	
private:

	uint32 PlayerPickedCount = 0;
};
