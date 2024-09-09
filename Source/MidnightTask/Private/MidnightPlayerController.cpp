// Fill out your copyright notice in the Description page of Project Settings.

#include "MidnightPlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"

void AMidnightPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	check(PlayerContext);
	UEnhancedInputLocalPlayerSubsystem* EnhancedInputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(EnhancedInputLocalPlayerSubsystem);
	EnhancedInputLocalPlayerSubsystem->AddMappingContext(PlayerContext, 0);
}

void AMidnightPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	EnableInput(this);
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &ThisClass::Jump);
}

void AMidnightPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);
 
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
 
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void AMidnightPlayerController::Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddControllerPitchInput(LookAxisVector.Y);
		ControlledPawn->AddControllerYawInput(LookAxisVector.X);
	}
}

void AMidnightPlayerController::Jump(const FInputActionValue& InputActionValue)
{
	if (ACharacter* ControlledCharacter = GetPawn<ACharacter>())
	{
		ControlledCharacter->Jump();
	}
}

