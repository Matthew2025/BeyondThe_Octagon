// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/Generators/EnvQueryGenerator_Cone.h"
#include "FreeflowCombat_EQSGetBack.generated.h"

/**
 * 
 */
UCLASS()
class BEYONDTHE_OCTAGON_API UFreeflowCombat_EQSGetBack : public UEnvQueryGenerator_Cone
{
	GENERATED_BODY()

public:
	virtual void GenerateItems(FEnvQueryInstance& QueryInstance) const override;

	virtual FText GetDescriptionTitle() const override;

	
};


