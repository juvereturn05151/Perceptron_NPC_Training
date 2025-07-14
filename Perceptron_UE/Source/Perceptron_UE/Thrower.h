// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Thrower.generated.h"

// Forward declarations
// class UPerceptron; 
class UInputMappingContext;
class UInputAction;

UCLASS()
class PERCEPTRON_UE_API AThrower : public AActor
{
	GENERATED_BODY()

	
public:	
	// Sets default values for this actor's properties
	AThrower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Category = "Throw")
	TSubclassOf<class AActor> SpherePrefab;

	UPROPERTY(EditAnywhere, Category = "Throw")
	TSubclassOf<class AActor> CubePrefab;

	UPROPERTY(EditAnywhere, Category = "Throw")
	UMaterialInterface* GreenMaterial;

	UPROPERTY(EditAnywhere, Category = "Throw")
	UMaterialInterface* RedMaterial;

private:
	// UPROPERTY()
	// UPerceptron* Perceptron;

	void SpawnObject(TSubclassOf<AActor> Prefab, UMaterialInterface* Material,
		FVector Location, FRotator Rotation/*, int32 ShapeType, int32 ColorType, int32 Output*/);

};
