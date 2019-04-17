// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPSAIGuard.generated.h"

class UPawnSensingComponent;
class UCapsuleComponent;


UENUM(BlueprintType)
enum class EAIState : uint8
{
	Idle,
	Suspicious,
	Alerted
};

UCLASS()
class FPSGAME_API AFPSAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPSAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//UPROPERTY(VisibleAnywhere, Category = "Components")
	//UCapsuleComponent* OverlapComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UPawnSensingComponent* PawnSensingComp;

	UFUNCTION()
	void OnPawnSeen(APawn* SeenPawn);

	UFUNCTION()
	void OnNoiseHeard(APawn* PawnHeard, const FVector& Location, float Volume);

	FRotator OriginalRotation;
	
	FTimerHandle TimerHandle_ResetOrientation;

	UFUNCTION()
	void ResetOrientation();

	EAIState GuardState;

	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
	void OnStateChange(EAIState NewState);
	

	//AI Patrol Challenge Code

	//should guard go on patrol?
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI")
	bool Patrol;

	//first point for patrol path
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "Patrol"))
	AActor* FirstPatrolPoint;

	//second point for patrol path
	UPROPERTY(EditInstanceOnly, Category = "AI", meta = (EditCondition = "Patrol"))
	AActor* SecondPatrolPoint;

	//current point the AI is either moving to or standing at
	AActor* CurrentPatrolPoint;


	void MoveToNextPatrolPoint();

	UFUNCTION()
	void onOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool fromSweep, const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
	
};
