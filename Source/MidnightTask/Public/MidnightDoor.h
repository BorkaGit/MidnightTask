// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MidnightDoor.generated.h"

UCLASS()
class MIDNIGHTTASK_API AMidnightDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	
	AMidnightDoor();
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void OpenDoor();
	
	UFUNCTION(BlueprintCallable)
	void CloseDoor();

	UFUNCTION(BlueprintCallable)
	bool IsDoorOpen() { return bIsDoorOpen; }
	
protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;
	
	UPROPERTY(EditAnywhere)
	float RotationSpeed = 45.f;

	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> OpeningSound
	;
	UPROPERTY(EditAnywhere)
	TObjectPtr<USoundBase> ClosingSound;
	
private:	
	bool bIsDoorOpen = false;

	FRotator InitialRotation;
	FRotator TargetRotation;
};
