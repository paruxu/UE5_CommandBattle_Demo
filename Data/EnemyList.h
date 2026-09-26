// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "EnemyList.generated.h"

class USkeletalMesh; //スケルタルメッシュを登録する

// 敵ステータスを登録するストラクタ
USTRUCT(BlueprintType)
struct FEnemyData
{
    GENERATED_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
    FText EnemyName;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy", meta = (ClampMin = "1"))
    int32 MaxHP = 100;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
    int32 AttackPower = 10;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
    int32 DefensePower = 10;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
    int32 MagicPower = 10;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
    int32 Speed = 10;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
    int32 DropExp = 100;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
    USkeletalMesh* EnemyMesh = nullptr;

};

// 敵ステータスを登録するデータアセット
UCLASS(BlueprintType)
class TESTGAME_API UEnemyList : public UDataAsset
{
    GENERATED_BODY()

public:

    // 敵ID(FName型のKey値)＋ストラクタのデータアセット。敵ステータスを登録
    // 値はエディタ上のみ編集可能、BP上では読み取り専用
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Enemy")
    TMap<FName, FEnemyData> Enemies;

};