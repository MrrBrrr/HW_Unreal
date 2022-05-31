// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BbRock.generated.h"

class UBoxComponent;

UCLASS()
class BIBLEBLACK_API ABbRock final : public AActor
{
	GENERATED_BODY()

public:
	// -- CONSTRUCTOR --
	// Sets default values for this actor's properties
	ABbRock();

	// -- PROPERTIES --
	// Simple component for attach 3d model to this actor
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="ActorMeshComponents")
	UStaticMeshComponent* StaticMeshComponent;

	// More variables for test visible scope
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category="FloaterVectors")
	FVector WorldOrigin;

	// Floating Speed
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="FloaterVectors",
	meta = (ClampMin = "0.1", EditCondition = "bShouldFloat"))
	float Speed;

	// Is this Actor should float?
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="FloaterVectors")
	bool bShouldFloat;

	UFUNCTION(BlueprintImplementableEvent, Category = "CustomEvents")
	void AfterHitEvent(AActor* OtherActor);

	// -- FUNCTIONS --	
	// Called every frame
	virtual void Tick(const float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	// -- COMPONENTS --
	UPROPERTY(VisibleAnywhere, Category="Components")
	UBoxComponent* HitBox;

	// -- FUNCTIONS --
	// Custom Hit functions using the Component specific signatures.
	// Hit begin function
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent,
	           AActor* OtherActor,
	           UPrimitiveComponent* OtherComp,
	           FVector NormalImpulse,
	           const FHitResult& Hit);
};
