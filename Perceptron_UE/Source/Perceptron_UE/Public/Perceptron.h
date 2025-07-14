// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Perceptron_UE/Perceptron_UECharacter.h"
#include "Perceptron.generated.h"

USTRUCT(BlueprintType)
struct FTrainingSet
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<double> Input;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	double Output;
};

class Perceptron_UECharacter;

UCLASS()
class PERCEPTRON_UE_API APerceptron : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APerceptron();

private:
	double DotProductBias(const TArray<double>& v1, const TArray<double>& v2);
	double CalcOutput(int32 i);
	double CalcOutput(double i1, double i2);
	double ActivationFunction(double dp);
	void InitializeWeights();
	void UpdateWeights(int32 j);
	void TrainPerceptron();

protected: 
	UPROPERTY(VisibleAnywhere, Category = "Info")
	TArray<FTrainingSet> trainingSets;
	UPROPERTY(VisibleAnywhere, Category = "Info")
	TArray<double> weights;
	UPROPERTY(VisibleAnywhere, Category = "Info")
	double bias;
	UPROPERTY(VisibleAnywhere, Category = "Info")
	double totalError;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	UPROPERTY()
	APerceptron_UECharacter* NPC;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SendInput(double i1, double i2, double o);

	void ResetTrainingSets()
	{
		trainingSets.Empty();
		totalError = 0.0;
		InitializeWeights();
	}

};
