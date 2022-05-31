// Fill out your copyright notice in the Description page of Project Settings.


#include "Snake/BbSpeedBonus.h"

#include "Snake/BbSnakeActorBase.h"

// Sets default values
ABbSpeedBonus::ABbSpeedBonus()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABbSpeedBonus::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ABbSpeedBonus::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Interaction with snake - change movement speed
void ABbSpeedBonus::Interact(AActor* Interaction, bool bIsHead)
{
    if (bIsHead)
    {
        ABbSnakeActorBase* Snake = Cast<ABbSnakeActorBase>(Interaction);
        if (IsValid(Snake))
        {
            Snake->IncreaseSnakeSpeed(5);
            this->Destroy();
        }
    }
}
