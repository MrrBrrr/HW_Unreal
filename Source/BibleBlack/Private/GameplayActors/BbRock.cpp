// Fill out your copyright notice in the Description page of Project Settings.


#include "GameplayActors/BbRock.h"

#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

#define PRINT_STRING(String) GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, String)

// Sets default values
ABbRock::ABbRock()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Set up the OverlapBox
	HitBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
	// Set as root component
	RootComponent = HitBox;
	HitBox->OnComponentHit.AddDynamic(this, &ABbRock::OnHit);

	// Make setting meshes possible 
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CustomStaticMesh"));
	StaticMeshComponent->SetupAttachment(GetRootComponent());

	WorldOrigin = FVector(0.0f);
	Speed = 1.0f;

	bShouldFloat = false;
}

// Called when the game starts or when spawned
void ABbRock::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABbRock::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bShouldFloat)
	{
		AddActorWorldOffset(GetActorRotation().Vector() * Speed, true);
	}
}

// ReSharper disable once CppMemberFunctionMayBeStatic
void ABbRock::OnHit(UPrimitiveComponent* HitComponent,
                     // ReSharper disable once CppParameterMayBeConstPtrOrRef
                     AActor* OtherActor,
                     UPrimitiveComponent* OtherComp,
                     FVector NormalImpulse,
                     const FHitResult& Hit)
{	
	// Rotate the Rock
	const FVector Direction = GetActorForwardVector();
	const FVector ReflectionVector = FMath::GetReflectionVector(Direction, Hit.Normal);
	FVector Normalized = FVector(ReflectionVector.X, ReflectionVector.Y, 0.0f);
	Normalized.Normalize();
	const FRotator Rotation = UKismetMathLibrary::MakeRotFromX(Normalized);
	SetActorRotation(Rotation);

	// PRINT_STRING(
	// 	FString::Printf(TEXT(
	// 			"Hit: %s"
	// 		),
	// 		*OtherActor->GetName()
	// 	));
	
	AfterHitEvent(OtherActor);
}
