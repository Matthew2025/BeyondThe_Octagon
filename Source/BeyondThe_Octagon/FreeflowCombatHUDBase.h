// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "FreeflowCombatHUDBase.generated.h"

/**
 * 
 */
UCLASS()
class BEYONDTHE_OCTAGON_API AFreeflowCombatHUDBase : public AHUD
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable, Category = "HUD")
	void SetUpHUD();
	
};
