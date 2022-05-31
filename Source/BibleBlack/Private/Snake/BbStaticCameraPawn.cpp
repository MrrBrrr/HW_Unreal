// Fill out your copyright notice in the Description page of Project Settings.


// ReSharper disable CppMemberFunctionMayBeConst
#include "Snake/BbStaticCameraPawn.h"

#include "Camera/CameraComponent.h"
#include "Snake/BbSnakeActorBase.h"
#include "Components/InputComponent.h"
#include "Snake/BbCutBonus.h"
#include "Snake/BbSpeedBonus.h"
#include "Snake/Food.h"

DEFINE_LOG_CATEGORY_STATIC(LogSnakeCameraPawn, All, All);

// Sets default values
ABbStaticCameraPawn::ABbStaticCameraPawn()
{
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    PawnCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("PawnCamera"));
    RootComponent = PawnCamera;
}

// Called when the game starts or when spawned
void ABbStaticCameraPawn::BeginPlay()
{
    Super::BeginPlay();
    SetActorRotation(FRotator(-90, 0, 0));

    CreateSnakeActor();

    // Start spawning food and bonuses
    GetWorldTimerManager().SetTimer(SnakeBonusTimerHandle, this,
                                    &ABbStaticCameraPawn::SpawnAnyBonus, Rate,
                                    true,
                                    Delay);

    Origin = FVector(0, 0, 0);
    Radius = 500;
}

// Called every frame
void ABbStaticCameraPawn::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ABbStaticCameraPawn::SetupPlayerInputComponent(
    UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this,
                                   &ABbStaticCameraPawn::HandlePlayerVerticalInput);
    PlayerInputComponent->BindAxis("MoveRight", this,
                                   &ABbStaticCameraPawn::HandlePlayerHorizontalInput);
}

// Spawn snake actor
void ABbStaticCameraPawn::CreateSnakeActor()
{
    SnakeActor = GetWorld()->SpawnActor<ABbSnakeActorBase>(
        SnakeActorClass, FTransform());
}

// Bonus selector for SnakeBonusTimerHandle
void ABbStaticCameraPawn::SpawnAnyBonus()
{
    const float Rand = FMath::FRandRange(0.0f, 1.0f);
    if (Rand < 0.7f)
    {
        SpawnFood();
    }
    else if (Rand < 0.9f)
    {
        SpawnSpeedBonus();
    }
    else
    {
        SpawnCutBonus();
    }
}

// Spawn food actor
void ABbStaticCameraPawn::SpawnFood()
{
    const FVector Location = GetRandomLocation();
    UE_LOG(LogSnakeCameraPawn, Display, TEXT("Spawning food at %s"),
           *Location.ToString())
    GetWorld()->SpawnActor<AFood>(SnakeBonusFoodClass, FTransform(Location));
}

// Spawn speed bonus actor
void ABbStaticCameraPawn::SpawnSpeedBonus()
{
    const FVector Location = GetRandomLocation();
    UE_LOG(LogSnakeCameraPawn, Display, TEXT("Spawning speed bonus at %s"),
           *Location.ToString())
    GetWorld()->SpawnActor<ABbSpeedBonus>(SnakeSpeedBonusClass,
                                          FTransform(Location));
}

// Spawn cut bonus actor
void ABbStaticCameraPawn::SpawnCutBonus()
{
    const FVector Location = GetRandomLocation();
    UE_LOG(LogSnakeCameraPawn, Display, TEXT("Spawning cut bonus at %s"),
           *Location.ToString())
    GetWorld()->SpawnActor<ABbCutBonus>(SnakeCutBonusClass,
                                        FTransform(Location));
}

// MoveForward
void ABbStaticCameraPawn::HandlePlayerVerticalInput(const float Value)
{
    if (IsValid(SnakeActor))
    {
        if (Value > 0 && SnakeActor->LastMoveDirection !=
            EMovementDirectionEnum::Down)
        {
            SnakeActor->BufferMoveDirection = EMovementDirectionEnum::Up;
            // SnakeActor->LastMoveDirection = EMovementDirectionEnum::Up;
        }
        else if (Value < 0 && SnakeActor->LastMoveDirection !=
                 EMovementDirectionEnum::Up)
        {
            SnakeActor->BufferMoveDirection = EMovementDirectionEnum::Down;
            // SnakeActor->LastMoveDirection = EMovementDirectionEnum::Down;
        }
    }
}

// MoveRight
void ABbStaticCameraPawn::HandlePlayerHorizontalInput(const float Value)
{
    if (IsValid(SnakeActor))
    {
        if (Value > 0 && SnakeActor->LastMoveDirection !=
            EMovementDirectionEnum::Right)
        {
            SnakeActor->BufferMoveDirection = EMovementDirectionEnum::Left;
            // SnakeActor->LastMoveDirection = EMovementDirectionEnum::Left;
        }
        else if (Value < 0 && SnakeActor->LastMoveDirection !=
                 EMovementDirectionEnum::Left)
        {
            SnakeActor->BufferMoveDirection = EMovementDirectionEnum::Right;
            // SnakeActor->LastMoveDirection = EMovementDirectionEnum::Right;
        }
    }
}

// Get random point from the NavMesh
FVector ABbStaticCameraPawn::GetRandomLocation()
{
    const int32 RandX = FMath::RandRange(-Radius, Radius);
    const int32 RandY = FMath::RandRange(-Radius, Radius);
    return FVector(RandX, RandY, 0);
}
