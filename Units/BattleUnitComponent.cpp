#include "BattleUnitComponent.h"

UBattleUnitComponent::UBattleUnitComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UBattleUnitComponent::BeginPlay()
{
    Super::BeginPlay();

    // 最大HPが最低1になるように補正
    MaxHP = FMath::Max(MaxHP, 1);

    // ゲーム開始時はHP Maxとする。
    CurrentHP = MaxHP;
}

int32 UBattleUnitComponent::ApplyDamage( UBattleUnitComponent* VL_Attacker, float VL_SkillMultiplier, UBattleUnitComponent* VL_Defender)
{
    double VL_Attack, VL_Defense, VL_Multiplier;

    VL_Attack = VL_Attacker->AttackPower;
    VL_Defense = VL_Defender->DefensePower;
    VL_Multiplier = VL_SkillMultiplier;

    // ダメージ＝攻撃力×技倍率×100/(100+防御力)×95%～105%。最低保証1
    int32 VL_CalculatedDamage = FMath::RoundToInt32((VL_Attack * VL_Multiplier * 100.0 / (100.0 + VL_Defense))* FMath::FRandRange(0.95f, 1.05f));

    if (VL_CalculatedDamage == 0)
    {
        VL_CalculatedDamage = 1;
    }   

   VL_Defender->CurrentHP -= VL_CalculatedDamage;

   return VL_CalculatedDamage;
}

//行動済みフラグの設定
void UBattleUnitComponent::SetActionFLG(bool bSetActionFLG)
{
    bActionFLG = bSetActionFLG;
}

// 未使用 1moreフラグの設定
void UBattleUnitComponent::Set1moreFLG(bool bSet1moreFLG)
{
    b1moreFLG = bSet1moreFLG;
}

void UBattleUnitComponent::SetCurrentHP(int32 NewCurrentHP)
{
    CurrentHP = FMath::Clamp(NewCurrentHP, 0, MaxHP);
}

//レベルアップ時のステータス上昇　（固定値で記述）
void UBattleUnitComponent::SetLevelUpStats()
{
	//Max HP:1.25倍、攻撃力:1.25倍、防御力:1.1倍、魔法力:2倍、素早さ:1.2倍
    //レベルアップ時に現在HPは"回復させない"

    MaxHP = FMath::RoundToInt32(
        static_cast<double>(MaxHP) * 1.25
    );

    AttackPower = FMath::RoundToInt32(
        static_cast<double>(AttackPower) * 1.25
    );

	DefensePower = FMath::RoundToInt32(
		static_cast<double>(DefensePower) * 1.1
	);

	MagicPower = FMath::RoundToInt32(
		static_cast<double>(MagicPower) * 2.0
	);

    Speed = FMath::RoundToInt32(
        static_cast<double>(Speed) * 1.2
    );
            
}

void UBattleUnitComponent::SetMaxHP(int32 VL_NewMaxHP)
{
    MaxHP = FMath::Max(1, VL_NewMaxHP);
}

//行動順決定処理 
// 引数：UBattleUnitComponentのポインタ配列（戦闘ユニットが格納される）
// 戻り値：素早さ順に並び替えたActorポインタ配列
TArray<AActor*> UBattleUnitComponent::SortBySpeed(TArray<UBattleUnitComponent*> VL_Units)
{
    TArray<UBattleUnitComponent*> VL_TMPSort;//素早さ順にUBattleUnitComponentを格納していく配列
    TArray<AActor*> VL_TurnOrder;            //素早さ順に整理された結果を格納する配列

    for (int32 i = 0; i < VL_Units.Num(); i++)
    {
		UBattleUnitComponent* VL_Unit = VL_Units[i];//VL_Unit=行動順を決定中の対象ユニット

        int32 VL_InsertIndex = VL_TMPSort.Num();//始めにVL_TMPSortの最後尾へ格納する

        // VL_TMPSortのループ
        for (int32 n = 0; n < VL_TMPSort.Num(); n++)
        {
            if (VL_Unit->Speed > VL_TMPSort[n]->Speed)
            {
                VL_InsertIndex = n;//自身より遅いSpeedを持つIndexの番号を取得
                break;
            }
        }

        VL_TMPSort.Insert(VL_Unit, VL_InsertIndex); // Indexの番号に格納
    }

    // VL_TMPSortを戻り値にセット
    for (int32 i = 0; i < VL_TMPSort.Num(); i++)
    {
        VL_TurnOrder.Add(VL_TMPSort[i]->GetOwner());
    }

    return VL_TurnOrder;
}

void UBattleUnitComponent::SetEnemyStatus(FName VL_EnemyID, FEnemyData VL_EnemyData)
{
    UnitID = VL_EnemyID.ToString();
    UnitFLG = 1;

    // データアセットのステータスをコピー
    MaxHP = VL_EnemyData.MaxHP;
    CurrentHP = MaxHP;
    AttackPower = VL_EnemyData.AttackPower;
    DefensePower = VL_EnemyData.DefensePower;
    MagicPower = VL_EnemyData.MagicPower;
    Speed = VL_EnemyData.Speed;
    DropExp = VL_EnemyData.DropExp;
    bActionFLG = false;
    b1moreFLG = false;
}
