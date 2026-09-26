# UE5 Command Battle Demo
- Unreal Engine 5で制作したコマンドバトルデモの、主要なC++ソースコードを記載します。

## 開発環境
- Unreal Engine 5.8.2
- Visual Studio

## フォルダ構成

| フォルダ | 役割 |
|---|---|
| `Core`| 戦闘に関する処理を配置 |
| `Data` | 敵のHPや攻撃力、経験値・メッシュを登録するData Assetの定義 |
| `Units` | 戦闘時の敵・味方ユニットの状態管理に関する処理を配置 |

※補足・・・ユニット戦闘時の敵・味方オブジェクトを「BattleUnit」として扱います

## 関数詳細
| ファイル | 関数名 | | 役割 |
|---|---|---|
| `Core/BattleResultCheck.cpp` |EvaluateBattleResult| 敵・味方のHPをチェックし、勝敗の判定を行う。 |
| `Core/RPGGameInstance.cpp` |CheckLevelUp| 現在の経験値≧レベルアップのために必要な経験値 であれば、レベルアップ処理を1回行う |
| `Core/RPGGameInstance.cpp` |SavePlayerStatsFromBattleUnit| RPGGameInstanceへステータスを保存する（戦闘終了後、現在HPを持ち越すため） |
| `Core/RPGGameInstance.cpp` |RestorePlayerStatsToBattleUnit|RPGGameInstanceへステータスを保存する（戦闘開始前、現在HPを設定するため） |
| `Core/RPGGameInstance.cpp` |GetEnemyDataByID|ストラクタ「FEnemyData」より敵ステタースを取得する |
| `Units/BattleUnitComponent.cpp` |ApplyDamage|攻撃側と防御側のステータスをもとに、ダメージ計算を行う |
| `Units/BattleUnitComponent.cpp` |ApplyDamage|攻撃側と防御側のステータスをもとに、ダメージ計算を行う |
| `Units/BattleUnitComponent.cpp` |ApplyDamage|攻撃側と防御側のステータスをもとに、ダメージ計算を行う |



## 設計上のポイント

### C++の処理をBlueprintから利用する
ダメージ計算や戦闘結果判定などを、Blueprintから呼び出して処理を構築した。
