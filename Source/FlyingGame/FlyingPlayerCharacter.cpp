// Fill out your copyright notice in the Description page of Project Settings.


#include "FlyingPlayerCharacter.h"

// Sets default values
AFlyingPlayerCharacter::AFlyingPlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFlyingPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFlyingPlayerCharacter::UpdateKeyPitch(float rate)
{
	if (FMath::Abs(rate) > 0.2f)
		UpdatePitch(rate * 2.0f);
}

void AFlyingPlayerCharacter::UpdateKeyRoll(float rate)
{
	if (FMath::Abs(rate) > 0.2f)
		UpdateRoll(rate * 2.0f);
}

void AFlyingPlayerCharacter::MouseXInputEvent(float amount)
{
	UpdatePitch(amount);
}

void AFlyingPlayerCharacter::MouseYInputEvent(float amount)
{
	UpdateRoll(amount);
}


void AFlyingPlayerCharacter::UpdatePitch(float rate)
{	
	bIsPitchKeyPressed = FMath::Abs(rate) > 0.0f;
	pitchSpeed = FMath::FInterpTo(pitchSpeed, rate * pitchRateMultiplier, GetWorld()->GetDeltaSeconds(), 2.0f);
}

void AFlyingPlayerCharacter::UpdateRoll(float rate)
{
	bIsRollKeyPressed = FMath::Abs(rate) > 0.0f;

	if (bIsPitchKeyPressed && !bIsRollKeyPressed) return;

	float targetSpeed = bIsRollKeyPressed ? (rate * rollRateMultiplier) : (GetActorRotation().Roll * -2.0f);

	rollSpeed = FMath::FInterpTo(rollSpeed, targetSpeed, GetWorld()->GetDeltaSeconds(), 2.0f);
}

// Called every frame
void AFlyingPlayerCharacter::Tick(float DeltaTime)
{
   Super::Tick(DeltaTime);
   //Movement or Thrust
   
   float newForwardSpeed = forwardSpeed + (-GetActorRotation().Pitch * Acceleration* DeltaTime);
   forwardSpeed = FMath::Clamp(newForwardSpeed, minSpeed, maxSpeed);

   AddActorLocalOffset(FVector(forwardSpeed * DeltaTime, 0.0f, 0.0f), true);
   //Rotation
   // FRotator(
	  // float InPitch,
	  // float InYaw,
	  // float InRoll
	  // )
   FRotator nR(pitchSpeed * DeltaTime, yawSpeed * DeltaTime, rollSpeed * DeltaTime);
   AddActorLocalRotation(nR);
}

void AFlyingPlayerCharacter::NotifyHit(UPrimitiveComponent* MyComp, AActor* Other, UPrimitiveComponent* OtherComp, bool bSelfMoved, 
	FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, 
		HitLocation, HitNormal, NormalImpulse, Hit);
	SetActorRotation(FQuat::Slerp(GetActorRotation().Quaternion(), HitNormal.ToOrientationQuat(),
		0.025f));
	//Deflect
	forwardSpeed = FMath::FInterpTo(forwardSpeed, minSpeed, GetWorld()->GetDeltaSeconds(), 5.0f);

	//ToDo reduce Health 
	//Add particle effect
}

// Called to bind functionality to input
void AFlyingPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("Turn", this, &AFlyingPlayerCharacter::MouseXInputEvent);
	PlayerInputComponent->BindAxis("TurnRate", this, &AFlyingPlayerCharacter::UpdateKeyRoll);
	PlayerInputComponent->BindAxis("LookUp", this, &AFlyingPlayerCharacter::MouseYInputEvent);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AFlyingPlayerCharacter::UpdateKeyPitch);

}

