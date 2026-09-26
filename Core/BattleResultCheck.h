// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BattleResultCheck.generated.h"

class UBattleUnitComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTGAME_API UBattleResultCheck : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBattleResultCheck();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	//バトルユニットを代入する配列
	UPROPERTY(EditAnywhere,  BlueprintReadWrite, Category = "Battle")
TArray<TObjectPtr<UBattleUnitComponent>> BattleUnits;

//戦闘結果判定　（戻り値：[0]継続、[1]勝利、[2]敗北）
UFUNCTION(BlueprintCallable, Category = "Battle")
int32 EvaluateBattleResult() const;
		
};
