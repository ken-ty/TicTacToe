/***********************************************/
/* @Title: Tic-Tac-Toe.c                       */
/*---------------------------------------------*/
/* @Auther: KenTOKURA                          */
/* @e-mail: s16c1089vn@s.chibakoudai.jp        */
/*---------------------------------------------*/
/* @Description:                               */
/*  M×Nの盤でK目並べをする。                   */
/*  player1は○, player2は×で表す。             */
/*---------------------------------------------*/
/* @version:1.00 (2019/07/19)                  */
/*  Create 3×3 game for PvP.                   */ 
/* @version:1.10 (2019/07/20)                  */
/*  Create Graphic of play Board.              */ 
/* @version:1.20 (2019/07/20)                  */
/*  Update Graphic to color.                   */ 
/* @version:1.30 (2019/07/20)                  */
/*  Create AI play thinking nothing and randam.*/
/* @version:1.40 (2019/07/20)                  */
/*  Create AI play search center square.       */
/* @version:1.41 (2019/07/21)                  */
/*  Update AI hide miss choice.                */
/***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> //注意...コンパイル時に-lmをつけること
#define M 3 
#define N 3 //M×N盤条件
#define K 3 //勝利条件

//マスの構造体
typedef struct tagSQUARE {
	int state; //状態... 0:空, 1:○, -1:×.
} tagSQUARE;

int InitialBoard( tagSQUARE [M][N] ); //ボードの初期化
int Input( tagSQUARE [M][N], int ); //入力 
int PrintBoard( tagSQUARE [M][N] );  //ボードの状態の出力
int SearchWinner( tagSQUARE [M][N] ); //勝敗チェック
void PrintResult( int ); //結果の出力

int AI_Input( tagSQUARE [M][N], int ); //AIの入力 

int main(void) 
{
	int i, j;
	int turn;
    int player; //player1: 1, player2: -1.
	tagSQUARE square[M][N]; //M×Nの盤 

	printf("Tic-Tac-Toe start!\n");

	//ボードの生成
	InitialBoard(square); //ボードの初期化
	printf("Create %d×%d board.\n\n", M, N);
	PrintBoard(square);
	
	//プレイ
    turn = 0;
	while ( SearchWinner(square) == 0 ) { 
        player = (int)pow( -1, turn ); 
		printf("\nturn %d\nPlayer%d.", turn, turn % 2 + 1 ); 
        printf("player = %d\n",player);
        if (player < 0) {
            Input( square, player );
        } else {
            AI_Input( square, player );
        }
		PrintBoard( square );
		if ( turn >= M *N -1 ) break; //全部おいたらloopを抜ける
		turn++;
	}
    //結果の出力
    PrintResult( SearchWinner(square) ); 

	return 0;
}	

//ボードの初期化
//square[M][N]のすべての.stateに0で初期化
int InitialBoard(tagSQUARE square[M][N]) {
	int i, j;
	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
			square[i][j].state = 0; //0...空
		}
	}

    return 0;
}

/*
プレイヤーの入力
ボードとプレイヤーを引数にとり、
関数内でプレイヤーが入力したマスにプレイヤーの数字を入れる。
*/

int Input(tagSQUARE square[M][N], int player) {
	int tate, yoko;
	int flag; //異常入力検知
	do {
		flag = 0;
		printf(" Where is put?\n");
		printf("tate:");
		scanf("%d", &tate);
		printf("yoko:");
		scanf("%d", &yoko);
		printf("\n");
		if ((tate > M || tate <= 0 ) || (yoko > N || yoko <= 0 )) {
			printf("error1: tateは1 ~ %d, yokoは1 ~ %d の数字で入力してください\n\n", M, N);
			flag = 1;
		} else if (square[tate-1][yoko-1].state != 0){
			printf("error2: 別のマスを入力してください\n\n");
			flag = 1;
		}
	} while (flag); //正常な入力がされるまで繰り返す。

	square[tate-1][yoko-1].state = player; //選択したマスにプレイヤーを入力

    return 0;
}

//ボードの状態を出力する。
int PrintBoard(tagSQUARE square[M][N]) {
	int i, j;
	for (i = 0; i < M; i++) {
		printf("%2d | ", i+1); //横ライン番号
		for (j = 0; j < N; j++) {
            printf("\x1b[47m");
			if (square[i][j].state == 1) {
                printf("\x1b[31m");
				printf(" ○ ");
                printf("\x1b[39m");
			}else if (square[i][j].state == -1) {
                printf("\x1b[34m");
				printf(" × ");
                printf("\x1b[39m");
			} else {
				printf("   ");
			}
            printf("\x1b[49m");
		}
		printf("\n");
	}
    printf("---+-");
	for (i = 0; i < N; i++) {
        printf("---");
    }
    printf("\n");
    printf("    ");
	for (i = 0; i < N; i++) {
        printf(" %2d", i+1 ); //縦ライン番号
    }
    printf("\n");
	return 0;
}

//勝利条件を満たしているかどうか調べる。
int SearchWinner( tagSQUARE square[M][N] ) {
	int i, j, k;
	int cnt;
	// 横のライン
	for( i=0; i<M; i++ ){
		for( j=0; j<N-(K-1); j++ ){
			cnt = 1;
			for( k=1; k<K; k++ ) {
                if ( square[i][j].state == 0 ) break; //空なら数えない
                //連続で並んでいる数を数える
                else if ( square[i][j].state == square[i][j+k].state ) cnt++;
			}
			if ( cnt >= K ) {
                return square[i][j].state; //勝った方の数字を返す
			}
		}
	}
	// 縦のライン
	for( i=0; i<M-(K-1); i++ ){
		for( j=0; j<N; j++ ){
			cnt = 1;
			for( k=1; k<K; k++ ) {
                if ( square[i][j].state == 0 ) break; //空なら数えない
                //連続で並んでいる数を数える
                else if ( square[i][j].state == square[i+k][j].state ) cnt++;
			}
			if ( cnt >= K ) {
                return square[j][i].state; //勝った方の数字を返す
			}
		}
	}
	//左斜めのライン
	for( i=0; i<M-(K-1); i++ ){
		for( j=0; j<N-(K-1); j++ ){
			cnt = 1;
			for( k=1; k<K; k++ ) {
                if ( square[i][j].state == 0 ) break; //空なら数えない
                //連続で並んでいる数を数える
                else if ( square[i][j].state == square[i+k][j+k].state ) cnt++;
			}
			if ( cnt >= K ) {
                return square[i][j].state; //勝った方の数字を返す
			}
		}
	}
	//右斜めのライン
    for( i=0; i<M-(K-1); i++ ){
        for( j=(K-1); j<N; j++ ){
			cnt = 1;
			for( k=1; k<K; k++ ) {
                if ( square[i][j].state == 0 ) break; //空なら数えない
                //連続で並んでいる数を数える
                else if ( square[i][j].state == square[i+k][j-k].state ) cnt++; 
            }
            if ( cnt >= K ) {
                return square[i][j].state; //勝った方の数字を返す
            }
		}
	}
	//どの勝利条件を満たしていない
	return 0;
}

//引数winnerに応じて結果の出力をする。
void PrintResult( int winner ) { 
    //player1の勝ち
    if ( winner == 1 ) { 
        printf("\x1b[31m");
        printf("\nPlayer 1");
        printf("\x1b[39m");
        printf(" is win!\n");
    }
    //player2の勝ち
    if ( winner == -1 ) { 
        printf("\x1b[34m");
        printf("\nPlayer -1");
        printf("\x1b[39m");
        printf(" is win!\n");
    }
    //引き分け
    if ( winner == 0) { 
        printf("\nDraw Game.\n");
    }
}

int AI_Input(tagSQUARE square[M][N], int player) {
	int tate, yoko;
	int flag; //異常入力検知
    srand( (unsigned)time( NULL ) ); //srandの初期化
	do {
		flag = 0;
		printf("== play AI ==\n");
        //tate,yokoを選ぶ
        if (square[1][1].state == 0) {
            tate = 2;
            yoko = 2;
        } else {
            tate = rand() % M + 1;
            yoko = rand() % N + 1;
        }
		printf("tate: %d\n", tate );
		printf("yoko: %d\n", yoko );
		if ((tate > M || tate <= 0 ) || (yoko > N || yoko <= 0 )) {
			flag = 1;
		} else if (square[tate-1][yoko-1].state != 0){
			flag = 1;
		}
	} while (flag); //正常な入力がされるまで繰り返す。

	square[tate-1][yoko-1].state = player; //選択したマスにプレイヤーを入力

    return 0;
