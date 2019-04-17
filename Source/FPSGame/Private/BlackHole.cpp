// Fill out your copyright notice in the Description page of Project Settings.

#include "BlackHole.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ABlackHole::ABlackHole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//add mesh comp; disbale collision, set mesh as root component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	//add inner sphere mesh; set radius as 100; attach comp to MeshComp
	InnerSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("InnerSphereComp"));
	InnerSphereComp->SetSphereRadius(100);
	InnerSphereComp->SetupAttachment(MeshComp);

	//Bind to event
	InnerSphereComp->OnComponentBeginOverlap.AddDynamic(this, &ABlackHole::OverlapInnerSphere);

	//add outer sphere mesh; set radius as 3000; attach comp to MeshComp
	OuterSphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("OuterSphereComp"));
	OuterSphereComp->SetSphereRadius(3000);
	OuterSphereComp->SetupAttachment(MeshComp);

}


void ABlackHole::OverlapInnerSphere(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool fromSweep, const FHitResult& SweepResult)
{
	if (OtherActor)
	{
		OtherActor->Destroy();
	}

}

/*// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
	
}
*/

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//Find all overlapping components that can collide and may be physically simulating and then pull them towards black hole spheres
	
	//create an array of overlapping components
	TArray<UPrimitiveComponent*> OverlappingComps;

	//get all overlapping components and put them in the array
	OuterSphereComp->GetOverlappingComponents(OverlappingComps);

	//iterate through the array of overlapping components until you reach the end
	for (int32 i = 0; i < OverlappingComps.Num(); i++)
	{
		//set the current overlapping comp as PrimComp
		UPrimitiveComponent* PrimComp = OverlappingComps[i];

		//if primComp which is the current comp both exists and is simulating physics then...
		if (PrimComp && PrimComp->IsSimulatingPhysics())
		{
			//create variable called sphereRadius and set it to outerSphere scale
			const float SphereRadius = OuterSphereComp->GetScaledSphereRadius();

			//create variable called ForceStrength and set it to -2000 so that it pulls towards the origin
			const float ForceStrength = -2000;

			//add a radial force to the prim comp which is the current comp
			PrimComp->AddRadialForce(GetActorLocation(), SphereRadius, ForceStrength, ERadialImpulseFalloff::RIF_Constant, true);
		}

	}


}

