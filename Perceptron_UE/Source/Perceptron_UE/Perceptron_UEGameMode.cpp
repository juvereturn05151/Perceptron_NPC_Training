// Copyright Epic Games, Inc. All Rights Reserved.

#include "Perceptron_UEGameMode.h"
#include "Perceptron_UECharacter.h"
#include "UObject/ConstructorHelpers.h"

APerceptron_UEGameMode::APerceptron_UEGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
