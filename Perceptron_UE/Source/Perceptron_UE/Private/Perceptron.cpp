// Fill out your copyright notice in the Description page of Project Settings.


#include "Perceptron.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APerceptron::APerceptron()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	weights.Init(0, 2);
}

// Called when the game starts or when spawned
void APerceptron::BeginPlay()
{
	Super::BeginPlay();

	// Find NPC in the world
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APerceptron_UECharacter::StaticClass(), FoundActors);

	if (FoundActors.Num() > 0)
	{
		NPC = Cast<APerceptron_UECharacter>(FoundActors[0]);
	}

	InitializeWeights();
}

double APerceptron::DotProductBias(const TArray<double>& v1, const TArray<double>& v2)
{
	if (v1.IsEmpty()|| v2.IsEmpty())
		return -1;

	if (v1.Num() != v2.Num())
		return -1;

	double d = 0;
	for (int32 i = 0; i < v1.Num(); i++)
	{
		d += v1[i] * v2[i];
	}
	return d + bias;
}

double APerceptron::CalcOutput(int32 i)
{
	return(ActivationFunction(DotProductBias(weights, trainingSets[i].Input)));
}

double APerceptron::CalcOutput(double i1, double i2)
{
	TArray<double> inp = { i1, i2 };
	return(ActivationFunction(DotProductBias(weights, inp)));
}

double APerceptron::ActivationFunction(double dp)
{
	if (dp > 0) return (1);
	return(0);
}

void APerceptron::InitializeWeights()
{
	for (int i = 0; i < weights.Num(); i++) 
	{
		weights[i] = FMath::FRandRange(-1.0, 1.0);
	}
	bias = FMath::FRandRange(-1.0, 1.0);
}

void APerceptron::UpdateWeights(int32 j)
{
	double error = trainingSets[j].Output - CalcOutput(j);
	totalError += FMath::Abs(static_cast<float>(error));
	for (int i = 0; i < weights.Num(); i++)
	{
		weights[i] = weights[i] + error * trainingSets[j].Input[i];
	}
	bias += error;
}

void APerceptron::TrainPerceptron()
{
	for (int t = 0; t < trainingSets.Num(); t++)
	{
		UpdateWeights(t);
	}
}

// Called every frame
void APerceptron::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APerceptron::SendInput(double i1, double i2, double o)
{
	double result = CalcOutput(i1, i2);
	UE_LOG(LogTemp, Log, TEXT("Result: %f"), result);

	if (IsValid(NPC))
	{
		USkeletalMeshComponent* SkeletalMesh = NPC->FindComponentByClass<USkeletalMeshComponent>();
		UPrimitiveComponent* Rigidbody = NPC->FindComponentByClass<UPrimitiveComponent>();

		if (result == 0.0)
		{
			NPC->Jump();

			if (Rigidbody)
			{
				Rigidbody->SetSimulatePhysics(true);
			}
		}
		else
		{
			if (Rigidbody)
			{
				Rigidbody->SetSimulatePhysics(false);
			}
		}
	}

	// Learn from it for next time
	FTrainingSet s;
	s.Input = { i1, i2 };
	s.Output = o;
	trainingSets.Add(s);

	TrainPerceptron();
}

