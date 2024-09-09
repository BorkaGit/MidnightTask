// Fill out your copyright notice in the Description page of Project Settings.


#include "MidnightDoor.h"

#include "Kismet/GameplayStatics.h"


AMidnightDoor::AMidnightDoor()
{
 
	PrimaryActorTick.bCanEverTick = true;

	DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	RootComponent = DoorMesh;
}


void AMidnightDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialRotation = DoorMesh->GetComponentRotation();
	TargetRotation = InitialRotation + FRotator(0.0f, -90.0f, 0.0f);
}

void AMidnightDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsDoorOpen)
	{
		FRotator CurrentRotation = DoorMesh->GetComponentRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, TargetRotation, DeltaTime, RotationSpeed);
		DoorMesh->SetWorldRotation(NewRotation);
	}
	else
	{
		FRotator CurrentRotation = DoorMesh->GetComponentRotation();
		FRotator NewRotation = FMath::RInterpTo(CurrentRotation, InitialRotation, DeltaTime, RotationSpeed);
		DoorMesh->SetWorldRotation(NewRotation);
	}
}

void AMidnightDoor::OpenDoor()
{
	UGameplayStatics::PlaySoundAtLocation(this,OpeningSound,GetActorLocation(),FRotator::ZeroRotator);
	bIsDoorOpen = true;
}

void AMidnightDoor::CloseDoor()
{
	UGameplayStatics::PlaySoundAtLocation(this,ClosingSound,GetActorLocation(),FRotator::ZeroRotator);
	bIsDoorOpen = false;
}
