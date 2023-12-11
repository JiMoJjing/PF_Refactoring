// Copyright Epic Games, Inc. All Rights Reserved.

#include "PF_RefactoringGameMode.h"
#include "PF_RefactoringCharacter.h"
#include "UObject/ConstructorHelpers.h"

APF_RefactoringGameMode::APF_RefactoringGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
