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

## 関数詳細
| ファイル | 関数名 | | 役割 |
|---|---||---|
| `Core/BattleResultCheck.cpp` |EvaluateBattleResult| 敵・味方のHPをチェックし、勝敗の判定を行う。 |
| `Core/RPGGameInstance.h / .cpp` || プレイヤー情報の保持・復元、レベルアップ判定、敵データ取得 |
| `Data/EnemyList.h / .cpp` || 敵の能力値・獲得経験値・メッシュを登録するData Assetの定義 |
| `Units/BattleUnitComponent.h / .cpp` || ユニットの状態管理、ダメージ計算、行動順の決定、レベルアップ時の能力値更新 |


## 設計上のポイント

### C++の処理をBlueprintから利用する
ダメージ計算や戦闘結果判定などを、Blueprintから呼び出して処理を構築した。
