// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Battle/Data/EnemyList.h"
#include "RPGGameInstance.generated.h"

class UBattleUnitComponent;

UCLASS()
class TESTGAME_API URPGGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:

    // レベルアップ判定
    UFUNCTION(BlueprintCallable, Category = "Player|Status")
    bool CheckLevelUp(UBattleUnitComponent* VL_TargetBattleUnit);
    
    // 現在HP
    UPROPERTY(BlueprintReadWrite, Category = "Player|Status")
    int32 VL_PlayerCurrentHP = 0;

    // 最大HP
    UPROPERTY(BlueprintReadWrite, Category = "Player|Status")
    int32 VL_PlayerMaxHP = 100;

    //ゲーム開始時、HPの初回引継が行われているか確認
    UPROPERTY(BlueprintReadWrite, Category = "Player|Status")
    bool bVL_HPcheck = false;

    // 現在Lv
    UPROPERTY(BlueprintReadWrite, Category = "Player|Status")
    int32 VL_PlayerLevel = 1;

    // 現在EXP
    UPROPERTY(BlueprintReadWrite, Category = "Player|Status")
    int32 VL_PlayerExp = 0;

    // レベルアップまでのEXP
    UPROPERTY(BlueprintReadWrite, Category = "Player|Status")
    int32 VL_PlayerExpToNextLevel = 100;

	// 戦闘終了後のステータスを記録
    UFUNCTION(BlueprintCallable, Category = "Player|Status")
    bool SavePlayerStatsFromBattleUnit(
        UBattleUnitComponent* VL_SourceBattleUnit);

    // 戦闘開始前のステータスを記録
    UFUNCTION(BlueprintCallable, Category = "Player|Status")
    bool RestorePlayerStatsToBattleUnit(
        UBattleUnitComponent* VL_TargetBattleUnit);

    // 攻撃力
    UPROPERTY(BlueprintReadWrite, Category = "Player|Status")
    int32 VL_PlayerAttackPower = 0;

    // 防御力
    UPROPERTY(BlueprintReadWrite, Category = "Player|Status")
    int32 VL_PlayerDefensePower = 0;

    // 魔力
    UPROPERTY(BlueprintReadWrite, Category = "Player|Status")
    int32 VL_PlayerMagicPower = 0;

    // 素早さ
    UPROPERTY(BlueprintReadWrite, Category = "Player|Status")
    int32 VL_PlayerSpeed = 0;

    // 全ステータスを保存済みか
    UPROPERTY(BlueprintReadOnly, Category = "Player|Status")
    bool bPlayerStatsSaved = false;

    // 戦闘開始時に指定する敵の種類(初期値=スライム赤)
    UPROPERTY(BlueprintReadWrite, Category = "Battle|Enemy")
    FName EncounterEnemyID = TEXT("E0001");

    // 敵ステータスをまとめたデータアセットへの参照
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Battle|Enemy")
    UEnemyList* EnemyDatabase = nullptr;

    // 敵IDから敵のステータスを取得
    UFUNCTION(BlueprintCallable, Category = "Battle|Enemy")
    bool GetEnemyDataByID(FName VL_EnemyID, FEnemyData& VL_OutEnemyData);

};
