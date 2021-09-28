// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FlyingPlayerCharacter.generated.h"

UCLASS()
class FLYINGGAME_API AFlyingPlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFlyingPlayerCharacter();

	UPROPERTY(EditAnywhere)
		float Acceleration;
	UPROPERTY(EditAnywhere)
		float minSpeed;
	UPROPERTY(EditAnywhere)
		float maxSpeed;

	float forwardSpeed; 
	float yawSpeed; 
	float pitchSpeed;
	float rollSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

publ