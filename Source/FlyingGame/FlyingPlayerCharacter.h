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

	UPROPERTY(EditAnywhere, Category = "Flight")
		float Acceleration = 30.0f;
	UPROPERTY(EditAnywhere, Category = "Flight")
		float minSpeed = 500.0f;
	UPROPERTY(EditAnywhere, Category = "Flight")
		float maxSpeed = 4000.0f;

	UPROPERTY(EditAnywhere, Category = "Flight")
	float forwardSpeed = 500.0f; 
	float yawSpeed; 
	float pitchSpeed;
	float rollSpeed;

	UPROPERTY(EditAnywhere, Category = "Flight")
	float rollRateMultiplier = 200;
	UPROPERTY(EditAnywhere, Category = "Flight")
	float pitchRateMultiplier = 200;

	bool bIsPitchKeyPressed = false;
	bool bIsRollKeyPressed = false;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void UpdateKeyPitch(float rate);
	void UpdateKeyRoll(float rate);

	void MouseXInputEvent(float amount);
	void MouseYInputEvent(float amount);

	//roatation
	void UpdatePitch(float rate);
	void UpdateRoll(float rate);
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called when a collision Occurs
	virtual void NotifyHit
	(
		class UPrimitiveComponent* MyComp,
		AActor* Other,
		class UPrimitiveComponent* OtherComp,
		bool bSelfMoved,
		FVector HitLocation,
		FVector HitNormal,
		FVector NormalImpulse,
		const FHitResult& Hit
	) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
