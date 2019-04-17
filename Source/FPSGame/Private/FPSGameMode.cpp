// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSGameMode.h"
#include "FPSHUD.h"
#include "FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AFPSGameMode::AFPSGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Blueprints/BP_Player"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AFPSHUD::StaticClass();


}


void AFPSGameMode::CompleteMission(APawn* InstigatorPawn, bool MissionSuccess)
{
	//disables input for the pawn that player is controlling but
	//still allows player to do things like access menus 
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);

		if (SpectatingViewportClass)
		{


			TArray<AActor*>ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingViewportClass, ReturnedActors);

			//change view target if any valid actor found
			if (ReturnedActors.Num() > 0)
			{
				AActor* NewViewTarget = ReturnedActors[0];

				APlayerController* Player = Cast<APlayerController>(InstigatorPawn->GetController());
				if (Player)
				{
					Player->SetViewTargetWithBlend(NewViewTarget, 0.5f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Spectating class is a nullptr, cannot change view targets. Update game mode class with valid subclass"));
		}

	}


	//let blueprints do the rest
	OnMissionCompleted(InstigatorPawn, MissionSuccess);




	
}


