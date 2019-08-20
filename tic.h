#ifndef HEADER_H
#define HEADER_H

// マクロ定数の定義
#define M 3 
#define N 3 //M×N盤条件
#define K 3 //勝利条件

//マスの構造体を定義
typedef struct tagSQUARE {
    int state;         //状態...0:空、1:〇、-1:×
    int AI_value;      //AIから見たそのマスの価値
    int User_value;    //Userから見たそのマスの価値
} tagSQUARE;

//関数を宣言
int InitialBoard( tagSQUARE [M][N] ); //ボードの初期化
int Input( tagSQUARE [M][N], int ); //入力 
int PrintBoard( tagSQUARE [M][N] );  //ボードの状態の出力
int SearchWinner( tagSQUARE [M][N] ); //勝敗チェック
void PrintResult( int ); //結果の出力
int evaluation( int overfield, int cnt_AI, int cnt_user, int cnt_void ); //評価テーブル
int EvaluateSquare( tagSQUARE [M][N], int i, int j ); //一つのマスの評価を更新
void UpdateEvaluate( tagSQUARE [M][N] );// 全てのマスの評価を更新
int AI_Input( tagSQUARE [M][N], int ); //AIの入力

#endif
