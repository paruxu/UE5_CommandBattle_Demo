# UE5 Command Battle Demo
- Unreal Engine 5で制作したコマンドバトルデモの、主要なC++ソースコードを公開します。

## 開発環境
- Unreal Engine 5.8.2
- Visual Studio

## 設計思想

- 戦闘時の敵・味方オブジェクトを「BattleUnit」として扱う。
- 戦闘中のHPなどはBattleUnitComponentのメンバ変数で管理する。
- 戦闘の進行処理はBlueprintで構築し、ダメージ計算や行動順判定などの処理はC++で関数を作成し呼び出す。

## フォルダ構成

| フォルダ | 役割 |
|---|---|
| `Core`| 戦闘に関する処理を配置 |
| `Data` | 敵の種類ごとのHPや攻撃力、経験値、メッシュなどを登録するData Assetを定義 |
| `Units` | 戦闘時の敵・味方ユニットの状態管理に関する処理を配置 |

## 関数詳細
| ファイル | 関数名 |　役割 |
|---|---|---|
| `Core/BattleResultCheck.cpp` |EvaluateBattleResult| 敵・味方のHPをチェックし、勝敗の判定を行う。 |
| `Core/RPGGameInstance.cpp` |CheckLevelUp| 現在の経験値≧レベルアップのために必要な経験値 であれば、レベルアップ処理を1回行う |
| `Core/RPGGameInstance.cpp` |SavePlayerStatsFromBattleUnit| RPGGameInstanceへステータスを保存する（戦闘終了後、現在HPを持ち越すため） |
| `Core/RPGGameInstance.cpp` |RestorePlayerStatsToBattleUnit|BattleUnitComponentへステータスを保存する（戦闘開始前、現在HPを設定するため） |
| `Core/RPGGameInstance.cpp` |GetEnemyDataByID|敵IDをキーにEnemyDatabaseを検索し、FEnemyDataを取得する|
| `Units/BattleUnitComponent.cpp` |ApplyDamage|攻撃側と防御側のステータスをもとに、ダメージを計算し、防御側のHPからダメージ値を減算する |
| `Units/BattleUnitComponent.cpp` |SetLevelUpStats|レベルアップ時の上昇ステータスを固定倍率で計算し、セットする |
| `Units/BattleUnitComponent.cpp` |SortBySpeed|ユニットが格納された配列を引数として受け取り、素早さ順に並び替えて戻す |
| `Units/BattleUnitComponent.cpp` |SetEnemyStatus|GetEnemyDataByIDと併用する。ストラクタ「FEnemyData」の敵ステータスをセットする |

## 注意
本リポジトリでは、ゲームで使用している主要なC++ソースコードを公開しています。本リポジトリ単体ではビルド・実行できません。
