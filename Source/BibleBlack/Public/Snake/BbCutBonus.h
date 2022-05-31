// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "GameFramework/Actor.h"
#include "BbCutBonus.generated.h"

UCLASS()
class BIBLEBLACK_API ABbCutBonus final : public AActor, public IInteractable
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ABbCutBonus();

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    // Interaction with snake - cut snake
    virtual void Interact(AActor* Interaction, bool bIsHead) override;
};
