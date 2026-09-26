# UE5 Command Battle Demo
- Unreal Engine 5で制作したコマンドバトルデモの、主要なC++ソースコードを記載します。

## 開発環境
- Unreal Engine 5.8
- Visual Studio

## フォルダ構成

| ファイル | 役割 |
|---|---|
| `Core`| 戦闘に関する処理 |
| `Data` | 敵の能力値・獲得経験値・メッシュを登録するData Assetの定義 |
| `Units/BattleUnitComponent.h / .cpp` | ユニットの状態管理、ダメージ計算、行動順の決定、レベルアップ時の能力値更新 |

## ソースコード構成

| ファイル | 役割 |
|---|---|
| `Core/BattleManager.h` | Blueprintで拡張するためのActor基底クラス |
| `Core/BattleResultCheck.h / .cpp` | 敵味方のHPによる戦闘結果判定 |
| `Core/RPGGameInstance.h / .cpp` | プレイヤー情報の保持・復元、レベルアップ判定、敵データ取得 |
| `Data/EnemyList.h / .cpp` | 敵の能力値・獲得経験値・メッシュを登録するData Assetの定義 |
| `Units/BattleUnitComponent.h / .cpp` | ユニットの状態管理、ダメージ計算、行動順の決定、レベルアップ時の能力値更新 |


## 設計上のポイント

### 敵の設定データと戦闘中の状態を分ける

敵の初期ステータスは `UEnemyList` に登録し、戦闘開始時に `UBattleUnitComponent` へコピーします。

敵の設定値と、ダメージによって変化する現在HPなどを分けて管理しています。

### 共通処理をActor Componentにまとめる

ユニットのステータスと関連処理を `UBattleUnitComponent` にまとめ、敵と味方で共通して扱える構成にしています。

### C++の処理をBlueprintから利用する

ダメージ計算や戦闘結果判定などを、`UFUNCTION(BlueprintCallable)` を通してBlueprintから呼び出せるようにしています。

### マップ移動をまたいでプレイヤー情報を保持する

`URPGGameInstance` にプレイヤーのHPや能力値を保持し、移動先のユニットへ復元する処理を用意しています。

## コードを見る際の入口

1. `BattleUnitComponent.cpp`：ダメージ計算と行動順の決定
2. `BattleResultCheck.cpp`：戦闘の終了条件
3. `RPGGameInstance.cpp`：レベルアップとステータス引き継ぎ
4. `EnemyList.h`：敵データの定義
