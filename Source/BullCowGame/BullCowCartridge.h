// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override; 
	virtual void OnInput(const FString& Input) override;

	void SetupGame();
	void WelcomeMsg();
	void DebugMsg();
	void ResetGame();
	void EndGame();
	void DeductLife();
	void ProcessGuess(FString Guess);
	bool IsIsogram(FString Word) const;
	bool IsIsogram2(FString Word) const;

	// Your declarations go below!
	private:
	bool bGameOver;
	int32 DEBUG; // Toggle debug messages
	int32 Lives; // Number of guesses
	FString HiddenWord; // Winning word	
	TArray<FString> Words;
};
