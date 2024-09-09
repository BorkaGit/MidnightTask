// Fill out your copyright notice in the Description page of Project Settings.


#include "MidnightPowerup_Base.h"

#include "MidnigthGameModeBase.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"


AMidnightPowerup_Base::AMidnightPowerup_Base()
{
	PrimaryActorTick.bCanEverTick =  false;
}

void AMidnightPowerup_Base::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	const ACharacter* OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OtherActor && OtherCharacter->IsPlayerControlled())
	{
		UGameplayStatics::PlaySoundAtLocation(this,PickupSound,GetActorLocation(),FRotator::ZeroRotator);
		Destroy();
		if (AMidnigthGameModeBase* GameModeBase = CastChecked<AMidnigthGameModeBase>(GetWorld()->GetAuthGameMode()))
			GameModeBase->AddPlayerPicked();
	}
}

