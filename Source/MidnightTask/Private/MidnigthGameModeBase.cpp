// Fill out your copyright notice in the Description page of Project Settings.


#include "MidnigthGameModeBase.h"

#include "EngineUtils.h"
#include "MidnightDoor.h"
#include "MidnightPowerup_Base.h"
#include "EnvironmentQuery/EnvQueryManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogGameModeBase, All, All);

static TAutoConsoleVariable CVarSpawnPickups(TEXT("su.SpawnPickups"), true, TEXT("Enable spawning of pickups via timer"), ECVF_Cheat);

void AMidnigthGameModeBase::StartPlay()
{
	Super::StartPlay();

	GetWorldTimerManager().SetTimer(TimerHandle_SpawnPickups, this, &ThisClass::SpawnPickupsTimerElapsed, SpawnPickupsTimerInterval, true);
}

void AMidnigthGameModeBase::SpawnPickupsTimerElapsed()
{
	if ( !CVarSpawnPickups.GetValueOnGameThread() )
	{
		UE_LOG(LogGameModeBase, Log, TEXT("Pickup spawning disabled via cvar 'CVarSpawnPickups'."));
		return;
	}

	int32 NumberOfAlivePickups = 0;
	
	for ( TActorIterator<AMidnightPowerup_Base> It(GetWorld()); It; ++It )
	{
		++NumberOfAlivePickups;
	}

	if (NumberOfAlivePickups >= MaxPickupsCount )
	{
		return;
	}
	
	UEnvQueryInstanceBlueprintWrapper* QueryInstance = UEnvQueryManager::RunEQSQuery(this, SpawnPickupsQuery, this, EEnvQueryRunMode::RandomBest5Pct, nullptr);
	if ( QueryInstance )
	{
		QueryInstance->GetOnQueryFinishedEvent().AddDynamic(this, &ThisClass::OnPickupSpawnQueryCompleted);
	}
}

void AMidnigthGameModeBase::OnPickupSpawnQueryCompleted(UEnvQueryInstanceBlueprintWrapper* QueryInstance, EEnvQueryStatus::Type QueryStatus)
{
	if ( QueryStatus != EEnvQueryStatus::Success )
	{
		UE_LOG(LogTemp, Warning, TEXT("Spawn pickup EQS Query Failed!"))
		return;
	}
	
	TArray<FVector> Locations = QueryInstance->GetResultsAsLocations();
	
	if ( !Locations.IsEmpty() )
	{
		GetWorld()->SpawnActor<AActor>(PickupClasses[FMath::RandRange(0, PickupClasses.Num() - 1)], Locations[0], FRotator::ZeroRotator);
	}
}

void AMidnigthGameModeBase::AddPlayerPicked()
{
	++PlayerPickedCount;
	if (PlayerPickedCount >= PlayerPickedGoal && !DoorToOpen.Get()->IsDoorOpen() )
	{
		DoorToOpen->OpenDoor();
	}
}