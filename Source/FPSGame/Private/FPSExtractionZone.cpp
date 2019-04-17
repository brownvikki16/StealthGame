// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSExtractionZone.h"
#include "Components/BoxComponent.h"
#include "Components/DecalComponent.h"
#include "FPSCharacter.h"
#include "FPSGameMode.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AFPSExtractionZone::AFPSExtractionZone()
{


	OverlapComp = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapComp"));	//assign overlapComp
	
	OverlapComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);				//set collision to query only; 
	/*Info on queries straight from documentation:
	This body is used only for spatial queries (ray casts, sweeps, and overlaps). 
	It cannot be used for simulation (rigid body, constraints). 
	This setting is useful for character movement and objects that do not 
	need physical simulation. Some performance gains are made by reducing 
	the data in the physics simulation tree.
	*/

	OverlapComp->SetCollisionResponseToAllChannels(ECR_Ignore);					//ignore all collisions
	OverlapComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);			//this object can overlap with Pawn
	OverlapComp->SetBoxExtent(FVector(200.0f));									//this is the unscaled size, before component scale is applied.
	RootComponent = OverlapComp;												//set as root component

	OverlapComp->SetHiddenInGame(false);										//make lines visible in game, even without rendered mesh

	OverlapComp->OnComponentBeginOverlap.AddDynamic(this, &AFPSExtractionZone::HandleOverlap); //call function HandleOverlap when pawn overlaps

	DecalComp = CreateDefaultSubobject<UDecalComponent>(TEXT("DecalComp"));	//assign decalComp
	DecalComp->DecalSize = FVector(200.0f, 200.0f, 200.0f);
	DecalComp->SetupAttachment(RootComponent);

}


//function for handling extraction zone
void AFPSExtractionZone::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	AFPSCharacter* MyPawn = Cast<AFPSCharacter>(OtherActor);
	if (MyPawn == nullptr)
	{
		return;
	}

	if (MyPawn->IsCarryingObjective)
	{

		//call game mode to handle the rest
		AFPSGameMode* GM = Cast<AFPSGameMode>(GetWorld()->GetAuthGameMode());
		if (GM)
		{
			GM->CompleteMission(MyPawn, true);
		}

	
	}
	else
	{
		UGameplayStatics::PlaySound2D(this, ObjectiveMissingSound);
	}

	//print message to console log when component overlaps
	//UE_LOG(LogTemp, Log, TEXT("Overlapped with extraction zone"));

}



