// Fill out your copyright notice in the Description page of Project Settings.

// ReSharper disable CppFunctionIsNotImplemented
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BbStaticCameraPawn.generated.h"

class ABbCutBonus;
class ABbSpeedBonus;
class AFood;
class ABbSnakeActorBase;
class UCameraComponent;

UCLASS()
class BIBLEBLACK_API ABbStaticCameraPawn final : public APawn
{
    GENERATED_BODY()

public:
    // Sets default values for this pawn's properties
    ABbStaticCameraPawn();

    // Static camera for a snake
    UPROPERTY(BlueprintReadWrite, Category="Snake")
    UCameraComponent* PawnCamera;

    // Created snake actor in BeginPlay()
    UPROPERTY(BlueprintReadWrite, Category="Snake")
    ABbSnakeActorBase* SnakeActor;

    // Ability for spawn any inherited blueprint
    UPROPERTY(EditDefaultsOnly, Category="Snake")
    TSubclassOf<ABbSnakeActorBase> SnakeActorClass;

    // Ability for a blueprint spawning
    UPROPERTY(EditDefaultsOnly, Category="Bonus")
    TSubclassOf<AFood> SnakeBonusFoodClass;

    // Ability for a blueprint spawning
    UPROPERTY(EditDefaultsOnly, Category="Bonus")
    TSubclassOf<ABbSpeedBonus> SnakeSpeedBonusClass;

    // Ability for a blueprint spawning
    UPROPERTY(EditDefaultsOnly, Category="Bonus")
    TSubclassOf<ABbCutBonus> SnakeCutBonusClass;

    // Radius for food spawning (set in BeginPlay)
    UPROPERTY(EditDefaultsOnly, Category="Bonus",
        meta = (ClampMin = "10", ClampMax = "600"))
    float Radius = 500.0f;

    // First bonus delay
    UPROPERTY(EditDefaultsOnly, Category="Bonus",
        meta = (ClampMin = "1", ClampMax = "100"))
    float Delay = 2.0f;

    // Bonus spawn rate
    UPROPERTY(EditDefaultsOnly, Category="Bonus",
        meta = (ClampMin = "1", ClampMax = "100"))
    float Rate = 3.0f;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    // Spawning bonus timer
    FTimerHandle SnakeBonusTimerHandle;
    // Default bonus spawn position (set in BeginPlay)
    FVector Origin;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(
        UInputComponent* PlayerInputComponent) override;

    // Spawn snake actor
    void CreateSnakeActor();

    // Bonus selector for SnakeBonusTimerHandle
    void SpawnAnyBonus();

    // Spawn food actor
    void SpawnFood();

    // Spawn speed bonus actor
    void SpawnSpeedBonus();

    // Spawn cut bonus actor
    void SpawnCutBonus();

    UFUNCTION()
    void HandlePlayerVerticalInput(float Value);
    UFUNCTION()
    void HandlePlayerHorizontalInput(float Value);

private:
    // Get random point in Radius
    FVector GetRandomLocation();
};
