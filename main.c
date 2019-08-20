/***********************************************/
/* @Title: main.c                              */
/*---------------------------------------------*/
/* @Auther: KenTOKURA                          */
/* @e-mail: s16c1089vn@s.chibakoudai.jp        */
/*---------------------------------------------*/
/* @Description:                               */
/*  M×Nの盤でK目並べをする。                  */
/*  AIは○, Userは×で表す。                   */
/*---------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> //注意...コンパイル時に-lmをつけること
#include "tic.h"

int main(void)
{
	int i, j;
	int turn;
    int player; //AI:1, User:-1.
	tagSQUARE square[M][N]; //M×Nの盤

	printf("Tic-Tac-Toe start!\n");

	//ボードの生成
	InitialBoard(square); //ボードの初期化
    //UpdateEvaluate(square); //評価関数の生成
    printf("Create %d×%d board.\n\n", M, N);
	PrintBoard(square);

	//プレイ
    turn = 1;
    //先攻後攻を決める。
    //-1か1でplayerを初期化
    srand( (unsigned)time( NULL ) ); //srandの初期化
    player = (int)pow( -1, rand()%2+1 );
	while ( SearchWinner( square ) == 0 ) {
        //更新結果を表示
        /*
        UpdateEvaluate( square ); //評価関数の更新
        printf("||\n");
        printf("||evaluation changed. \n");
        printf("\\/\n\n");
		PrintBoard( square );
        */
        player *= -1;
		printf("\nturn %d.\n", turn );
        //printf("player = %d\n",player); //debug用,playerを確認
        UpdateEvaluate(square); //評価関数の更新
        if (player < 0) {
            Input( square, player );
        } else {
            AI_Input( square, player );
        }
		PrintBoard( square );
		if ( turn >= M *N ) break; //全部おいたらloopを抜ける
		turn++;
	}
    //結果の出力
    PrintResult( SearchWinner(square) );

	return 0;
}