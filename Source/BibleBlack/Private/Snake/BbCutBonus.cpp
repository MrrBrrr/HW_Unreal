// Fill out your copyright notice in the Description page of Project Settings.


#include "Snake/BbCutBonus.h"

#include "Snake/BbSnakeActorBase.h"

// Sets default values
ABbCutBonus::ABbCutBonus()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABbCutBonus::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABbCutBonus::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Interaction with snake - cut snake
void ABbCutBonus::Interact(AActor* Interaction, bool bIsHead)
{
    if (bIsHead)
    {
        ABbSnakeActorBase* Snake = Cast<ABbSnakeActorBase>(Interaction);
        if (IsValid(Snake))
        {
            Snake->RemoveSnakeHalf();
            this->Destroy();
        }
    }
}

