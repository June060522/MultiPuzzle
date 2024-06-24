// Fill out your copyright notice in the Description page of Project Settings.


#include "MultiPuzzleGameInstance.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"
#include "Blueprint/UserWidget.h"

#include "MainMenu.h"
#include "MenuWidget.h"

UMultiPuzzleGameInstance::UMultiPuzzleGameInstance(const FObjectInitializer& ObjectInitializer)
{
	ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/MenuSystem/WBP_MainMenu"));

	if (MenuBPClass.Class)
	{
		MenuClass = MenuBPClass.Class;
	}

	ConstructorHelpers::FClassFinder<UUserWidget> InGameMenuBPClass(TEXT("/Game/MenuSystem/WBP_InGameMenu"));

	if (InGameMenuBPClass.Class)
	{
		InGameMenuClass = InGameMenuBPClass.Class;
	}
}

void UMultiPuzzleGameInstance::Init()
{
	Super::Init();
	UE_LOG(LogTemp, Warning, TEXT("GameInstance Init"));
}

void UMultiPuzzleGameInstance::LoadMenu()
{
	if (MenuClass)
	{
		Menu = CreateWidget<UMainMenu>(this, MenuClass);

		if (IsValid(Menu))
		{
			Menu->Setup();
			Menu->SetMenuInterface(this);
		}
	}
}

void UMultiPuzzleGameInstance::InGameLoadMenu()
{
	if (MenuClass)
	{
		UMenuWidget* MainMenu = CreateWidget<UMenuWidget>(this, InGameMenuClass);

		if (IsValid(MainMenu))
		{
			MainMenu->Setup();
			MainMenu->SetMenuInterface(this);
		}
	}
}

void UMultiPuzzleGameInstance::Host()
{
	if (Menu)
	{
		Menu->Teardown();
	}

	GEngine->AddOnScreenDebugMessage(0, 2, FColor::Green, TEXT("Hosting!"));
	if (GWorld)
	{
		UE_LOG(LogTemp, Log, TEXT("ServerTravel to /Game/FirstPerson/Maps/FirstPersonMap?listen"));
		//GWorld->ServerTravel("/Game/FirstPerson/Maps/FirstPersonMap?listen");
		GWorld->ServerTravel("/Game/Maps/Play?listen");
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to get World!"));
	}
}

void UMultiPuzzleGameInstance::Join(const FString& Address)
{
	if (Menu)
	{
		Menu->Teardown();
	}

	if (!ensure(GEngine != nullptr)) return;

	GEngine->AddOnScreenDebugMessage(0, 5, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController)
	{
		PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(0, 5, FColor::Red, FString::Printf(TEXT("Failed %s"), *Address));
	}
}

void UMultiPuzzleGameInstance::LoadMainMenu()
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (PlayerController)
	{
		PlayerController->ClientTravel("/Game/Maps/MainMenu?listen", ETravelType::TRAVEL_Absolute);
	}
}
