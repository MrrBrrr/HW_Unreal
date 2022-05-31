// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BbSnakeActorBase.generated.h"

class ABbSnakeElementBase;

UENUM()
enum class EMovementDirectionEnum
{
    Up,
    Down,
    Left,
    Right
};

UCLASS()
class BIBLEBLACK_API ABbSnakeActorBase final : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABbSnakeActorBase();

    UPROPERTY(EditDefaultsOnly, Category="Snake")
    TSubclassOf<ABbSnakeElementBase> SnakeElementClass;

    UPROPERTY(EditDefaultsOnly, Category="Snake")
    float ElementSize;

    UPROPERTY(EditDefaultsOnly, Category="Snake")
    float MovementSpeed;

    UPROPERTY(EditDefaultsOnly, Category="Snake",
        meta = (ClampMin = "0", ClampMax = "100"))
    float MovementSpeedWeight = 1;;

    UPROPERTY(BlueprintReadOnly, Category="Snake")
    TArray<ABbSnakeElementBase*> SnakeElements;

    UPROPERTY(BlueprintReadOnly, Category="Snake")
    EMovementDirectionEnum LastMoveDirection;

    UPROPERTY(BlueprintReadOnly, Category="Snake")
    EMovementDirectionEnum BufferMoveDirection;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    FTimerHandle ExitGameTimerHandle;
    float OriginalMovementSpeedWeight; // Affected by IncreaseSnakeSpeed

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Grow one additional element
    void AddSnakeElement();
    // Grow snake tail
    void AddSnakeElement(int ElementsNum);

    // Snake movement
    void Move();

    // Snake element hit something event
    void SnakeElementOverlap(ABbSnakeElementBase* OverlappedElement,
                             AActor* Other);

    // Speed bonus implementation
    void IncreaseSnakeSpeed(float Duration);

    // Cut snake bonus implementation
    void RemoveSnakeHalf();

    // End Game
    void KillSnake();

private:
    ABbSnakeElementBase* SpawnSnakeElement(const FVector ActorLocation);
    void SpeedToDefault();
    void ExitGame() const;
};
