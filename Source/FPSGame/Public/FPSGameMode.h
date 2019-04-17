// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPSGameMode.generated.h"

UCLASS()
class AFPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Spectating")
		TSubclassOf<AActor>SpectatingViewportClass;
	


public:

	AFPSGameMode();

	//function to end the mission
	void CompleteMission(APawn* InstigatorPawn, bool MissionSuccess);

	//function implemented by blueprint, not in code
	UFUNCTION(BlueprintImplementableEvent, Category = "GameMode")
		void OnMissionCompleted(APawn* InstigatorPawn, bool MissionSuccess);
};



