// Fill out your copyright notice in the Description page of Project Settings.


#include "Snake/BbSnakeWall.h"

#include "Snake/BbSnakeActorBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogSnakeWall, All, All);

// Sets default values
ABbSnakeWall::ABbSnakeWall()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABbSnakeWall::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ABbSnakeWall::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Interaction with snake - crash snake
void ABbSnakeWall::Interact(AActor* Interaction, const bool bIsHead)
{
    if (bIsHead)
    {
        ABbSnakeActorBase* Snake = Cast<ABbSnakeActorBase>(Interaction);
        if (IsValid(Snake))
        {
            Snake->KillSnake();
        }
        else
        {
            UE_LOG(LogSnakeWall, Error,
                   TEXT("Wall interact - Snake is not valid"))
        }
    }
}
