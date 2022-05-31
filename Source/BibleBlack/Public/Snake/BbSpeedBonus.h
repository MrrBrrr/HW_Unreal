// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "BbSpeedBonus.generated.h"

UCLASS()
class BIBLEBLACK_API ABbSpeedBonus final : public AActor, public IInteractable
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABbSpeedBonus();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    // Interaction with snake - change movement speed
    virtual void Interact(AActor* Interaction, bool bIsHead) override;
};
