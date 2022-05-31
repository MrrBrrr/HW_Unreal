// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "BbSnakeElementBase.generated.h"

class ABbSnakeActorBase;

UCLASS()
class BIBLEBLACK_API ABbSnakeElementBase final : public AActor,
                                                 public IInteractable
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABbSnakeElementBase();

    // Set in blueprints
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components")
    UStaticMeshComponent* MeshComponent;

    // Set by SnakeActorBase when call AddSnakeElement
    UPROPERTY()
    ABbSnakeActorBase* SnakeOwner;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Interaction with another actors 
    virtual void Interact(AActor* Interaction, bool bIsHead) override;

    UFUNCTION()
    void HandleBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                            AActor* OtherActor,
                            UPrimitiveComponent* OtherComp,
                            int32 OtherBodyIndex,
                            bool bFromSweep,
                            const FHitResult& SweepResult);

    // Sets material for a head in blueprints
    UFUNCTION(BlueprintNativeEvent)
    void SetFirstElementType();

    // Switch collision enables on snake moving
    UFUNCTION()
    void ToggleCollision() const;
};
