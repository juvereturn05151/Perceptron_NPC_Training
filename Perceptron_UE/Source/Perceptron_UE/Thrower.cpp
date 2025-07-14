// Fill out your copyright notice in the Description page of Project Settings.


#include "Thrower.h"
#include "Logging/LogMacros.h"
#include "Perceptron_UE/Public/Perceptron.h"
// Sets default values
AThrower::AThrower()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AThrower::BeginPlay()
{
	Super::BeginPlay();
    if (PerceptronClass) // assuming you set this from Blueprint
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.Owner = this;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        Perceptron = GetWorld()->SpawnActor<APerceptron>(PerceptronClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnParams);
    }
}

// Called every frame
void AThrower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    CooldownTimer -= DeltaTime;

    if (CooldownTimer > 0.0f) return;

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (!PlayerController) return;



    if (PlayerController->IsInputKeyDown(EKeys::One))
    {
        SpawnObject(SpherePrefab, RedMaterial, GetActorLocation(), GetActorRotation(), 0, 0, 0);
    }
    else if (PlayerController->IsInputKeyDown(EKeys::Two))
    {
        SpawnObject(SpherePrefab, GreenMaterial, GetActorLocation(), GetActorRotation(), 0, 1, 1);
    }
    else if (PlayerController->IsInputKeyDown(EKeys::Three))
    {
        SpawnObject(CubePrefab, RedMaterial, GetActorLocation(), GetActorRotation(), 1, 0, 0);
    }
    else if (PlayerController->IsInputKeyDown(EKeys::Four))
    {
        SpawnObject(CubePrefab, GreenMaterial, GetActorLocation(), GetActorRotation(), 1, 1, 1);
    }
}

void AThrower::SpawnObject(TSubclassOf<AActor> Prefab, UMaterialInterface* Material,
    FVector Location, FRotator Rotation, int32 ShapeType, int32 ColorType, int32 Output)
{
    if (!Prefab || !Material || !Perceptron) return;

    UWorld* World = GetWorld();
    if (!World) return;

    FActorSpawnParameters SpawnParams;
    SpawnParams.Owner = this;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

    AActor* SpawnedActor = World->SpawnActor<AActor>(Prefab, Location, Rotation, SpawnParams);
    if (SpawnedActor)
    {
        UStaticMeshComponent* MeshComponent = SpawnedActor->FindComponentByClass<UStaticMeshComponent>();
        if (MeshComponent)
        {
            MeshComponent->SetMaterial(0, Material);

            if (MeshComponent->IsSimulatingPhysics())
            {
                MeshComponent->AddImpulse(GetActorForwardVector() * 500.0f, NAME_None, true);
            }
        }

        Perceptron->SendInput(ShapeType, ColorType, Output);
    }
    CooldownTimer = CooldownDuration;
}

