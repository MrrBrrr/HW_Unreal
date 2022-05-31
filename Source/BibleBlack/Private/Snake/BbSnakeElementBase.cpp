// Fill out your copyright notice in the Description page of Project Settings.


#include "Snake/BbSnakeElementBase.h"

#include "Snake/BbSnakeActorBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogSnakeElementBase, All, All);

// Sets default values
ABbSnakeElementBase::ABbSnakeElementBase()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(
        TEXT("MeshComponent"));
    SetRootComponent(MeshComponent);

    MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    MeshComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

// Called when the game starts or when spawned
void ABbSnakeElementBase::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ABbSnakeElementBase::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Interaction with another actors
void ABbSnakeElementBase::Interact(AActor* Interaction, bool bIsHead)
{
    ABbSnakeActorBase* Snake = Cast<ABbSnakeActorBase>(Interaction);
    if (IsValid(Snake))
    {
        Snake->KillSnake();
    }
    else
    {
        UE_LOG(LogSnakeElementBase, Error,
               TEXT("Snake element interact - Snake base is not valid"))
    }
}

// Bound to OnComponentBeginOverlap for MeshComponent
void ABbSnakeElementBase::HandleBeginOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    if (IsValid(SnakeOwner))
    {
        SnakeOwner->SnakeElementOverlap(this, OtherActor);
    }
}

// Switch collision enables on snake moving
void ABbSnakeElementBase::ToggleCollision() const
{
    if (MeshComponent->GetCollisionEnabled() == ECollisionEnabled::NoCollision)
    {
        MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    }
    else
    {
        MeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    }
}

// Sets material for a head in blueprints
void ABbSnakeElementBase::SetFirstElementType_Implementation()
{
    MeshComponent->OnComponentBeginOverlap.AddDynamic(
        this, &ABbSnakeElementBase::HandleBeginOverlap);
}
