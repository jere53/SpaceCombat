// Copyright Epic Games, Inc. All Rights Reserved.

#include "SpaceCombatPawn.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Engine/World.h"
#include "Engine/StaticMesh.h"
#include "Weapons/Public/WeaponComponent.h"

ASpaceCombatPawn::ASpaceCombatPawn()
{
	// Structure to hold one-time initialization
	struct FConstructorStatics
	{
		ConstructorHelpers::FObjectFinderOptional<UStaticMesh> PlaneMesh;
		FConstructorStatics()
			: PlaneMesh(TEXT("/Game/Flying/Meshes/UFO.UFO"))
		{
		}
	};
	static FConstructorStatics ConstructorStatics;

	// Create static mesh component
	PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh0"));
	PlaneMesh->SetStaticMesh(ConstructorStatics.PlaneMesh.Get());	// Set static mesh
	RootComponent = PlaneMesh;

	// Create a spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->SetupAttachment(RootComponent);	// Attach SpringArm to RootComponent
	SpringArm->TargetArmLength = 160.0f; // The camera follows at this distance behind the character	
	SpringArm->SocketOffset = FVector(0.f,0.f,60.f);
	SpringArm->bEnableCameraLag = false;	// Do not allow camera to lag
	SpringArm->CameraLagSpeed = 15.f;

	// Create camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);	// Attach the camera
	Camera->bUsePawnControlRotation = false; // Don't rotate camera with controller

	// Set handling parameters
	Acceleration = 500.f;
	TurnSpeed = 50.f;
	MaxSpeed = 4000.f;
	MinSpeed = 500.f;
	RollSpeed = 50.f;
	CurrentForwardSpeed = 500.f;
	CurrentThrottle = 0.5f;
	ThrottleRate = 0.2f;

	HitPoints = 200;
}

void ASpaceCombatPawn::Tick(float DeltaSeconds)
{

	if (HitPoints <= 0)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Green, FString::Printf(TEXT("Dead!")));
		}
		Destroy();
		return;
	}

	//AI SpacePawns are handled by adding forces from their AI Controller.
	if (!GetController()->IsPlayerController()) return;

	const FVector LocalMove = FVector(CurrentForwardSpeed * DeltaSeconds, 0.f, 0.f);

	// Move plan forwards (with sweep so we stop when we collide with things)
	AddActorLocalOffset(LocalMove, true);

	// Calculate change in rotation this frame
	FRotator DeltaRotation(0,0,0);
	DeltaRotation.Pitch = CurrentPitchSpeed * DeltaSeconds;
	DeltaRotation.Yaw = CurrentYawSpeed * DeltaSeconds;
	DeltaRotation.Roll = CurrentRollSpeed * DeltaSeconds;

	// Rotate plane
	AddActorLocalRotation(DeltaRotation);

	// Call any parent class Tick implementation
	Super::Tick(DeltaSeconds);
}

void ASpaceCombatPawn::NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit)
{
	Super::NotifyHit(MyComp, Other, OtherComp, bSelfMoved, HitLocation, HitNormal, NormalImpulse, Hit);

	// Deflect along the surface when we collide.
	FRotator CurrentRotation = GetActorRotation();
	SetActorRotation(FQuat::Slerp(CurrentRotation.Quaternion(), HitNormal.ToOrientationQuat(), 0.025f));
}

void ASpaceCombatPawn::BeginPlay()
{
	Super::BeginPlay();

	HitPoints = 200;

	TArray<UWeaponComponent*> WeaponComponents;
	GetComponents(WeaponComponents);
	for (UActorComponent* WC : WeaponComponents)
	{
		Weapons.Add((UWeaponComponent*)WC);
	}
}

float ASpaceCombatPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Blue, FString::Printf(TEXT("Current HP: %f"), HitPoints));
	}
	HitPoints -= DamageAmount;
	return DamageAmount;
}


void ASpaceCombatPawn::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    // Check if PlayerInputComponent is valid (not NULL)
	check(PlayerInputComponent);

	// Bind our control axis' to callback functions
	PlayerInputComponent->BindAxis("Throttle", this, &ASpaceCombatPawn::ThrottleInput);
	PlayerInputComponent->BindAxis("MoveUp", this, &ASpaceCombatPawn::MoveUpInput);
	PlayerInputComponent->BindAxis("RollClockwise", this, &ASpaceCombatPawn::RollClockwiseInput);
	PlayerInputComponent->BindAxis("YawRight", this, &ASpaceCombatPawn::YawRightInput);
	PlayerInputComponent->BindAction("FireTrigger", IE_Pressed, this, &ASpaceCombatPawn::FireWeapons);
}

void ASpaceCombatPawn::ThrottleInput(float Val)
{
	// Is there any input?
	bool bHasInput = !FMath::IsNearlyEqual(Val, 0.f);
	// If input is not held down, use current throttle
	//otherwise modify the throttle according to ThrottleRate
	if (bHasInput)
	{
		CurrentThrottle += Val * GetWorld()->GetDeltaSeconds() * ThrottleRate;
		CurrentThrottle = FMath::Clamp(CurrentThrottle, 0.f, 1.f); //throttle can go between 0 and 1 (0-100% throttle)
	}

	//always accelerate as much as possible
	float CurrentAcc = Acceleration;

	// Calculate new speed
	float NewForwardSpeed = CurrentForwardSpeed + (GetWorld()->GetDeltaSeconds() * CurrentAcc);
	// Clamp between MinSpeed and MaxSpeed, limited by Throttle
	CurrentForwardSpeed = FMath::Clamp(NewForwardSpeed, MinSpeed, CurrentThrottle * MaxSpeed);

	/*
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Throttle: %f"), CurrentThrottle));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Speed: %f"), CurrentForwardSpeed));
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, FString::Printf(TEXT("Acc: %f"), CurrentAcc));
	}
	*/
}

void ASpaceCombatPawn::MoveUpInput(float Val)
{
	if (bInvertUpInput) {
		Val *= -1;
	}

	// Target pitch speed is based in input
	float TargetPitchSpeed = (Val * TurnSpeed * -1.f);

	// When steering, we decrease pitch slightly
	TargetPitchSpeed += (FMath::Abs(CurrentYawSpeed) * -0.2f);

	// Smoothly interpolate to target pitch speed
	CurrentPitchSpeed = FMath::FInterpTo(CurrentPitchSpeed, TargetPitchSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void ASpaceCombatPawn::RollClockwiseInput(float Val)
{
	float TargetRollSpeed = (Val * RollSpeed);

	// Smoothly interpolate roll speed
	CurrentRollSpeed = FMath::FInterpTo(CurrentRollSpeed, TargetRollSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void ASpaceCombatPawn::YawRightInput(float Val)
{
	// Target yaw speed is based on input
	float TargetYawSpeed = (Val * TurnSpeed);

	// Smoothly interpolate to target yaw speed
	CurrentYawSpeed = FMath::FInterpTo(CurrentYawSpeed, TargetYawSpeed, GetWorld()->GetDeltaSeconds(), 2.f);
}

void ASpaceCombatPawn::FireWeapons()
{

	if (Weapons.Num() == 0)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, FString::Printf(TEXT("NO WEAPONS!")));
		}

		return;
	}

	for (UWeaponComponent* Wep : Weapons)
	{
		Wep->FireWeapon(GetOwner(), this);
	}
}

FVector ASpaceCombatPawn::GetVelocity() const
{
	return GetActorForwardVector() *= CurrentForwardSpeed;
}

float ASpaceCombatPawn::GetMaxSpeed() const
{
	return MaxSpeed;
}

FVector ASpaceCombatPawn::GetPosition() const
{
	return GetActorLocation();
}

float ASpaceCombatPawn::GetMaxAcceleration() const
{
	//we divide by two to get max turn speed per second (since input lerps over 2 seconds)
	float MaxDegreeRotInSecond = TurnSpeed / 2;

	return MaxDegreeRotInSecond;
}

AActor* ASpaceCombatPawn::GetFleeTarget() const
{
	return IBoidInterface::GetFleeTarget();
}
