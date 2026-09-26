//各ユニットのステータスを変数として管理する為のコンポーネント

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Battle/Data/EnemyList.h"
#include "BattleUnitComponent.generated.h"

UCLASS(ClassGroup = (Battle), meta = (BlueprintSpawnableComponent))
class TESTGAME_API UBattleUnitComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UBattleUnitComponent();

    void SetLevelUpStats();

	// ユニットIDを取得
    UFUNCTION(BlueprintPure, Category = "Battle|Status")
    FString GetUnitID() const { return UnitID; }

    // 敵・味方フラグを取得
    UFUNCTION(BlueprintPure, Category = "Battle|Status")
    int32 GetUnitFLG() const { return UnitFLG; }

    // 最大HPを取得
    UFUNCTION(BlueprintPure, Category = "Battle|Status")
    int32 GetMaxHP() const { return MaxHP; }

    UFUNCTION(BlueprintCallable, Category = "Battle|Status")
    void SetMaxHP(int32 VL_NewMaxHP);

    // 現在HPを取得
    UFUNCTION(BlueprintPure, Category = "Battle|Status")
    int32 GetCurrentHP() const { return CurrentHP; }

    // 行動済みフラグを取得
    UFUNCTION(BlueprintPure, Category = "Battle|Status")
    bool GetActionFLG() const { return bActionFLG; }

    // 1moreフラグを取得
    UFUNCTION(BlueprintPure, Category = "Battle|Status")
    bool Get1moreFLG() const { return b1moreFLG; }
    
    // DropExpを取得
    UFUNCTION(BlueprintPure, Category = "Battle|Status")
    int32 GetDropExp() const { return DropExp; }

	// 引数  ：攻撃側BattleUnitComponent、技倍率、守備側BattleUnitComponent
    // 戻り値：ダメージ実数
    UFUNCTION(BlueprintCallable, Category = "Battle|Status")
    static int32 ApplyDamage(
        UBattleUnitComponent* VL_Attacker,
        float VL_SkillMultiplier,
        UBattleUnitComponent* VL_Defender);

	// 行動済みフラグを変更
    UFUNCTION(BlueprintCallable, Category = "Battle|Status")
    void SetActionFLG(bool bSetActionFLG);

    //未実装 1moreフラグを変更
    UFUNCTION(BlueprintCallable, Category = "Battle|Status")
    void Set1moreFLG(bool bSet1moreFLG);

    // 現在HPを引数の値で上書き
    UFUNCTION(BlueprintCallable, Category = "Battle|Status")
    void SetCurrentHP(int32 NewCurrentHP);

    //インスタンスへセットする　※ UE側で使用しない場合、UFUNCTIONは不要
    int32 GetAttackPower() const { return AttackPower; }
    int32 GetDefensePower() const { return DefensePower; }
    int32 GetMagicPower() const { return MagicPower; }
    int32 GetSpeed() const { return Speed; }

    void SetAttackPower(int32 VL_Value) { AttackPower = VL_Value; }
    void SetDefensePower(int32 VL_Value) { DefensePower = VL_Value; }
    void SetMagicPower(int32 VL_Value) { MagicPower = VL_Value; }
    void SetSpeed(int32 VL_Value) { Speed = VL_Value; }

    // 素早さチェック。同速の場合はプレイヤー優先
    UFUNCTION(BlueprintCallable, Category = "Battle|Turn")
    static TArray<AActor*> SortBySpeed(TArray<UBattleUnitComponent*> VL_Units);

    // 敵のステータスをセット
    UFUNCTION(BlueprintCallable, Category = "Battle|Enemy")
    void SetEnemyStatus(FName VL_EnemyID, FEnemyData VL_EnemyData);

protected:
    virtual void BeginPlay() override;

private:

    // バトルユニットステータス（UE5の詳細にて手動設定 ）
    
    // UnitID
    UPROPERTY(EditAnywhere, Category = "Battle|Status")
    FString UnitID = TEXT("0000");

    // 敵・味方フラグ(0＝味方、1＝敵)
    UPROPERTY(EditAnywhere, Category = "Battle|Status", 
    meta = (ClampMin = "0", ClampMax = "1"))
    int32 UnitFLG = 0;
       
	// 最大HP
    UPROPERTY(EditAnywhere, Category = "Battle|Status",
        meta = (ClampMin = "1"))
    int32 MaxHP = 100;

    // 現在HP
    UPROPERTY(VisibleAnywhere, Category = "Battle|Status")
    int32 CurrentHP = 0;

    // 攻撃力
    UPROPERTY(EditAnywhere, Category = "Battle|Status")
    int32 AttackPower = 0;

    // 防御力
    UPROPERTY(EditAnywhere, Category = "Battle|Status")
    int32 DefensePower = 0;

    // 魔力
    UPROPERTY(EditAnywhere, Category = "Battle|Status")
    int32 MagicPower = 0;

    // 素早さ
    UPROPERTY(EditAnywhere, Category = "Battle|Status")
    int32 Speed = 0;

	//行動済みフラグ
	UPROPERTY(VisibleAnywhere, Category = "Battle|Status")
    bool bActionFLG = false;

    //1moreフラグ
    UPROPERTY(VisibleAnywhere, Category = "Battle|Status")
    bool b1moreFLG = false;

    //落とす経験値
    UPROPERTY(EditAnywhere, Category = "Battle|Status")
    int32 DropExp = 0;

};