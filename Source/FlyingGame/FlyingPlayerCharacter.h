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
		float Acceleration = 30.0f;
	UPROPERTY(EditAnywhere)
		float minSpeed = 500.0f;
	UPROPERTY(EditAnywhere)
		float maxSpeed = 4000.0f;

	float forwardSpeed; 
	float yawSpeed; 
	float pitchSpeed;
	float rollSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateKeyPitch(float rate);
	void UpdateKeyRoll(float rate);

	void mouseXInputEvent(float amount);
	void mouseYInputEvent(float amount);

	//roatation
	void UpdatePitch(float rate);
	void UpdateRoll(float rate);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
