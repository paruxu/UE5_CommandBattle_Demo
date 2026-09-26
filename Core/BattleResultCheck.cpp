// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/Core/BattleResultCheck.h"
#include "BattleResultCheck.h"
#include "Battle/Units/BattleUnitComponent.h"

//戦闘結果判定処理
int32 UBattleResultCheck::EvaluateBattleResult() const
{
	bool bVL_PlayerAlive = false; //味方が生存してればtrueに
	bool bVL_EnemyAlive = false; //敵が生存していればtrueに

	for (const auto& Unit : BattleUnits)
	{
		const int32 VL_UnitFLG = Unit->GetUnitFLG();
		const int32 VL_UnitCurrentHP = Unit->GetCurrentHP();

		if (VL_UnitFLG == 0 && VL_UnitCurrentHP > 0)//味方の生存確認
		{
			bVL_PlayerAlive = true;
		}

		if (VL_UnitFLG == 1 && VL_UnitCurrentHP > 0) //敵の生存確認
		{
			bVL_EnemyAlive = true;
		}

	}

	// 敗北（敵が全滅していても、プレイヤーの全滅を優先する）
	if (!bVL_PlayerAlive)
	{
		return 2;
	}

	// 勝利
	if (!bVL_EnemyAlive)
	{
		return 1;
	}

	// 両方に生存者がいる：戦闘継続
	return 0;

}


// Sets default values for this component's properties
UBattleResultCheck::UBattleResultCheck()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UBattleResultCheck::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

// Called every frame
void UBattleResultCheck::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

