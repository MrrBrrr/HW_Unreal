// Fill out your copyright notice in the Description page of Project Settings.


#include "Snake/BbSnakeActorBase.h"

#include "Snake/BbSnakeElementBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogSnakeActorBase, All, All);

// Sets default values
ABbSnakeActorBase::ABbSnakeActorBase()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    ElementSize = 100.f;
    MovementSpeed = 50.f;
    LastMoveDirection = EMovementDirectionEnum::Down;
    BufferMoveDirection = EMovementDirectionEnum::Down;
}

// 
ABbSnakeElementBase* ABbSnakeActorBase::SpawnSnakeElement(
    const FVector ActorLocation)
{
    // Shift element to the end 
    const FVector NewLocation(
        ActorLocation.X + SnakeElements.Num() * ElementSize,
        ActorLocation.Y,
        ActorLocation.Z);
    const FTransform Transform(NewLocation);
    ABbSnakeElementBase* SnakeElement = GetWorld()->SpawnActor<
        ABbSnakeElementBase>(SnakeElementClass, Transform);
    SnakeElement->SnakeOwner = this;

    // Remember every single tail section
    SnakeElements.Add(SnakeElement);
    return SnakeElement;
}

//
void ABbSnakeActorBase::SpeedToDefault()
{
    MovementSpeedWeight = OriginalMovementSpeedWeight;
}

// Called when the game starts or when spawned
void ABbSnakeActorBase::BeginPlay()
{
    Super::BeginPlay();

    OriginalMovementSpeedWeight = MovementSpeedWeight;

    // MovementSpeed shows how many seconds snake will be moving by exactly one ElementSize  
    SetActorTickInterval(MovementSpeed);
    // Spawn tail 
    AddSnakeElement(5);
}

// Called every frame
void ABbSnakeActorBase::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);

    Move();

    // For a speed bonus
    SetActorTickInterval(MovementSpeed * (1 / MovementSpeedWeight));
}

// Grow one additional element
void ABbSnakeActorBase::AddSnakeElement()
{
    const FVector ActorLocation = GetActorLocation();
    ABbSnakeElementBase* SnakeElement = SpawnSnakeElement(ActorLocation);
    // To prevent appearance in map center
    SnakeElement->SetActorHiddenInGame(true);
}

// Grow snake tail
void ABbSnakeActorBase::AddSnakeElement(const int ElementsNum)
{
    const FVector ActorLocation = GetActorLocation();

    // If it is head
    ABbSnakeElementBase* HeadSnakeElement = SpawnSnakeElement(
        ActorLocation);
    HeadSnakeElement->SetFirstElementType();

    for (int i = 1; i < ElementsNum; i++)
    {
        SpawnSnakeElement(ActorLocation);
    }
}

// Snake movement
// TODO: it could be done by input key events
void ABbSnakeActorBase::Move()
{
    FVector MovementVector(ForceInitToZero);
    LastMoveDirection = BufferMoveDirection;
    switch (LastMoveDirection)
    {
        case EMovementDirectionEnum::Up:
            MovementVector.X += ElementSize;
            break;
        case EMovementDirectionEnum::Down:
            MovementVector.X -= ElementSize;
            break;
        case EMovementDirectionEnum::Left:
            MovementVector.Y += ElementSize;
            break;
        case EMovementDirectionEnum::Right:
            MovementVector.Y -= ElementSize;
            break;
    }

    // Disable collision to prevent snake collide with itself
    SnakeElements[0]->ToggleCollision();

    // Snake tail
    for (int i = SnakeElements.Num() - 1; i > 0; i--)
    {
        ABbSnakeElementBase* CurrentElement = SnakeElements[i];
        const ABbSnakeElementBase* PrevElement = SnakeElements[i - 1];
        FVector PrevLocation = PrevElement->GetActorLocation();
        CurrentElement->SetActorLocation(PrevLocation);
        CurrentElement->SetActorHiddenInGame(false);
        // disabled in ABbSnakeActorBase::AddSnakeElement()
    }

    // Snake head
    SnakeElements[0]->AddActorLocalOffset(MovementVector);
    // Enable collision back
    SnakeElements[0]->ToggleCollision();
}

// Snake element hit something event
void ABbSnakeActorBase::SnakeElementOverlap(
    ABbSnakeElementBase* OverlappedElement, AActor* Other)
{
    if (IsValid(OverlappedElement))
    {
        int32 ElemIndex;
        SnakeElements.Find(OverlappedElement, ElemIndex);
        const bool bIsFirst = ElemIndex == 0;
        IInteractable* InteractableInterface = Cast<IInteractable>(Other);
        if (InteractableInterface)
        {
            InteractableInterface->Interact(this, bIsFirst);
        }
    }
}

// Speed bonus implementation
void ABbSnakeActorBase::IncreaseSnakeSpeed(const float Duration)
{
    FTimerHandle SpeedTimerHandle;
    GetWorldTimerManager().SetTimer(SpeedTimerHandle, this,
                                    &ABbSnakeActorBase::SpeedToDefault,
                                    Duration, false);

    MovementSpeedWeight = MovementSpeedWeight * 3;
}

// Cut snake bonus implementation
void ABbSnakeActorBase::RemoveSnakeHalf()
{
    const int Half = SnakeElements.Num() / 2;
    for (int i = 1; i < Half; i++)
    {
        ABbSnakeElementBase* Pop = SnakeElements.Pop();
        Pop->Destroy();
    }
}

// End Game
void ABbSnakeActorBase::KillSnake()
{
    UE_LOG(LogSnakeActorBase, Display, TEXT("Snake %s is dead"), *GetName())
    SetActorTickEnabled(false);

    GetWorldTimerManager().SetTimer(ExitGameTimerHandle, this,
                                    &ABbSnakeActorBase::ExitGame, 0.5f, false);
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void ABbSnakeActorBase::ExitGame() const
{
    UWorld* World = GetWorld();
    if (!ensure(World!=nullptr))
    {
        UE_LOG(LogSnakeActorBase, Error, TEXT("No UWorld"))
        return;
    }

    APlayerController* PlayerController = World->GetFirstPlayerController();
    if (!ensure(PlayerController!=nullptr))
    {
        UE_LOG(LogSnakeActorBase, Error, TEXT("No APlayerController"))
        return;
    }

    UE_LOG(LogSnakeActorBase, Display, TEXT("Exit game command"))
    PlayerController->ConsoleCommand("quit");
}
