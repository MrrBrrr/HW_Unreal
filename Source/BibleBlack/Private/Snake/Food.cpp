// Fill out your copyright notice in the Description page of Project Settings.


#include "Snake/Food.h"

#include "Snake/BbSnakeActorBase.h"

// Sets default values
AFood::AFood()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AFood::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void AFood::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Interaction with snake - collecting food and grow
void AFood::Interact(AActor* Interaction, const bool bIsHead)
{
    if (bIsHead)
    {
        ABbSnakeActorBase* Snake = Cast<ABbSnakeActorBase>(Interaction);
        if (IsValid(Snake))
        {
            Snake->AddSnakeElement();
            this->Destroy();
        }
    }
}
