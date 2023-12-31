// Copyright Epic Games, Inc. All Rights Reserved.
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "AI/Public/BoidInterface.h"
#include "SpaceCombatPawn.generated.h"

class UWeaponComponent;

UCLASS(Config=Game)
class SHIPS_API ASpaceCombatPawn : public APawn, public IBoidInterface
{
	GENERATED_BODY()

	/** StaticMesh component that will be the visuals for our flying pawn */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* PlaneMesh;

	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* Camera;

	/** Array that holds the weapons after they've been spawned**/
	UPROPERTY(Category = Weapons, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TArray<UWeaponComponent*> Weapons;

	/** Array that holds the weapons after they've been spawned**/
	UPROPERTY(Category = HP, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		float HitPoints;

public:
	ASpaceCombatPawn();

	// Begin AActor overrides
	virtual void Tick(float DeltaSeconds) override;
	virtual void NotifyHit(class UPrimitiveComponent* MyComp, class AActor* Other, class UPrimitiveComponent* OtherComp, bool bSelfMoved, FVector HitLocation, FVector HitNormal, FVector NormalImpulse, const FHitResult& Hit) override;
	virtual void BeginPlay() override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;
	// End AActor overrides

protected:

	// Begin APawn overrides
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override; // Allows binding actions/axes to functions
	// End APawn overrides

	/** Bound to the thrust axis */
	void ThrottleInput(float Val);
	
	/** Bound to the vertical axis */
	void MoveUpInput(float Val);

	/** Bound to the horizontal axis */
	void RollClockwiseInput(float Val);

	/** Bound to dedicated buttons*/
	void YawRightInput(float Val);

	UFUNCTION()
	void FireWeapons();

private:

	/** How quickly forward speed changes */
	UPROPERTY(Category=Plane, EditAnywhere)
	float Acceleration;

	/** How quickly pawn can steer */
	UPROPERTY(Category=Plane, EditAnywhere)
	float TurnSpeed;

	/** Max forward speed */
	UPROPERTY(Category = Plane, EditAnywhere)
	float MaxSpeed;

	/** Min forward speed */
	UPROPERTY(Category=Plane, EditAnywhere)
	float MinSpeed;

	/** How quickly pawn can roll*/
	UPROPERTY(Category = Roll, EditAnywhere)
		float RollSpeed;

	/** Current forward speed */
	float CurrentForwardSpeed;

	/** Current yaw speed */
	float CurrentYawSpeed;

	/** Current pitch speed */
	float CurrentPitchSpeed;

	/** Current roll speed */
	float CurrentRollSpeed;

	/**Current Throttle setting**/
	float CurrentThrottle;

	/**How much does the throttle increase each second, if trying to get to full throttle**/
	float ThrottleRate;

	/**Should we invert the input to go up**/
	bool bInvertUpInput;

public:
	/** Returns PlaneMesh subobject **/
	FORCEINLINE class UStaticMeshComponent* GetPlaneMesh() const { return PlaneMesh; }
	/** Returns SpringArm subobject **/
	FORCEINLINE class USpringArmComponent* GetSpringArm() const { return SpringArm; }
	/** Returns Camera subobject **/
	FORCEINLINE class UCameraComponent* GetCamera() const { return Camera; }

	// Inherited via IBoidInterface
	virtual FVector GetVelocity() const override;
	virtual float GetMaxSpeed() const override;
	virtual FVector GetPosition() const override;
	virtual float GetMaxAcceleration() const override;
	virtual AActor* GetFleeTarget() const override;
};
