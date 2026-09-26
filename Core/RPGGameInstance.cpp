// Fill out your copyright notice in the Description page of Project Settings.


#include "Battle/Core/RPGGameInstance.h"
#include "Battle/Units/BattleUnitComponent.h"

bool URPGGameInstance::CheckLevelUp(
    UBattleUnitComponent* VL_TargetBattleUnit)
{
	bool bVL_LevelUp = false;

    // EXPが多い場合でも1回レベルアップとする。（BP側で本処理を複数回呼ぶ）
    if (VL_PlayerExp >= VL_PlayerExpToNextLevel)
    {
        // 現在EXPからレベルアップ分のEXPを引く
        VL_PlayerExp -= VL_PlayerExpToNextLevel;

        // 次回の必要EXP＝1.5倍固定値でセット
        VL_PlayerExpToNextLevel = FMath::RoundToInt32(
            static_cast<double>(VL_PlayerExpToNextLevel) * 1.5
        );

        // レベルを1上げる
        ++VL_PlayerLevel;

        // 指定したユニットのステータスを更新
        VL_TargetBattleUnit->SetLevelUpStats();

        //インスタンスの最大HPへ、レベルアップ後のHPを保存
		VL_PlayerMaxHP = VL_TargetBattleUnit->GetMaxHP();

        bVL_LevelUp = true;

    }

    return bVL_LevelUp;
}

// BattleUnitComponentからRPGGameInstanceへステータスを保存
bool URPGGameInstance::SavePlayerStatsFromBattleUnit(
    UBattleUnitComponent* VL_SourceBattleUnit)
{
    // 参照が無効であればエラー
    if (!IsValid(VL_SourceBattleUnit))
    {
        return false;
    }

    VL_PlayerMaxHP = VL_SourceBattleUnit->GetMaxHP();
    VL_PlayerCurrentHP = VL_SourceBattleUnit->GetCurrentHP();
    VL_PlayerAttackPower = VL_SourceBattleUnit->GetAttackPower();
    VL_PlayerDefensePower = VL_SourceBattleUnit->GetDefensePower();
    VL_PlayerMagicPower = VL_SourceBattleUnit->GetMagicPower();
    VL_PlayerSpeed = VL_SourceBattleUnit->GetSpeed();

    bPlayerStatsSaved = true; //RPGGameInstanceへの保存済フラグ

    return true;
}

// RPGGameInstanceからBattleUnitComponentへステータスを保存
bool URPGGameInstance::RestorePlayerStatsToBattleUnit(
    UBattleUnitComponent* VL_TargetBattleUnit)
{

	// 復元先が無効、またはRPGGameInstanceへの保存済フラグがfalseならエラー
    if (!IsValid(VL_TargetBattleUnit) || !bPlayerStatsSaved)
    {
        return false;
    }

    VL_TargetBattleUnit->SetMaxHP(VL_PlayerMaxHP);
    VL_TargetBattleUnit->SetCurrentHP(VL_PlayerCurrentHP);
    VL_TargetBattleUnit->SetAttackPower(VL_PlayerAttackPower);
    VL_TargetBattleUnit->SetDefensePower(VL_PlayerDefensePower);
    VL_TargetBattleUnit->SetMagicPower(VL_PlayerMagicPower);
    VL_TargetBattleUnit->SetSpeed(VL_PlayerSpeed);

    return true;
}

// 敵IDから敵データアセットを取得
bool URPGGameInstance::GetEnemyDataByID(FName VL_EnemyID, FEnemyData& VL_OutEnemyData)
{
    VL_OutEnemyData = FEnemyData();

    // 敵データアセットへの参照が無効ならエラー
    if (!IsValid(EnemyDatabase))
    {
        return false;
    }

    FEnemyData* VL_FoundData = EnemyDatabase->Enemies.Find(VL_EnemyID);

    // 敵データアセットへの参照がnullならエラー
    if (VL_FoundData == nullptr)
    {

        return false;
    }

    VL_OutEnemyData = *VL_FoundData;

    return true;
}