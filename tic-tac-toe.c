/***********************************************/
/* @Title: Tic-Tac-Toe.c                       */
/*---------------------------------------------*/
/* @Auther: KenTOKURA                          */
/* @e-mail: s16c1089vn@s.chibakoudai.jp        */
/*---------------------------------------------*/
/* @Description:                               */
/* 	N×Mの盤でK目並べをする。M=3,N=3のみ対応    */
/* 	player1は○, player2は×で表す。             */
/*---------------------------------------------*/
/* @version:1.00 (2019/07/19)                  */
/* 	Create 3×3 game for PvP.                   */ 
/***********************************************/

#include<stdio.h>
#define N 3 
#define M 3 //N×M盤条件
#define K 3 //勝利条件

//マスの構造体
typedef struct tagSQUARE {
	int state; //状態... 0:空, 1:○, 2:×.
} tagSQUARE;

void InitialBoard( tagSQUARE [N][M] ); //ボードの初期化
void Input(tagSQUARE [N][M], int ); //入力 
int SearchWinner( tagSQUARE [N][M] ); //勝敗チェック(3×3のみ対応)

int main(void) 
{
	int i, j;
	int turn = 0;
	tagSQUARE square[N][M]; 

	printf("Tic-Tac-Toe start!\n");

	//ボードの生成
	InitialBoard(square); //ボードの初期化
	printf("Create %d×%d board.\n", N, M);
	
	//プレイ
	while (SearchWinner(square) == 0) { 
		printf("\nturn %d\nPlayer%d.", turn, turn % 2 + 1); 
		Input(square, turn % 2 + 1);
		if (turn >= N *M -1) break; //全部おいたらloopを抜ける
		turn++;
	}

	//player1の勝ち
	if (SearchWinner(square) == 1) { 
		printf("\nPlayer 1 is win.\n");
	}
	//player2の勝ち
	if (SearchWinner(square) == -1) { 
		printf("\nPlayer 2 is win.\n");
	}
	//引き分け
	if (SearchWinner(square) == 0) { 
		printf("\nDraw Game.\n");
	}

	return 0;
}	

//そろったラインがあるか探索する。(3×3のみ対応)
int SearchWinner( tagSQUARE square[N][M]) {
	// 横のライン
	int i;
	for( i=0; i<N; i++){
		if (square[i][0].state == 1 && square[i][1].state == 1 && square[i][2].state == 1 ) {
			return 1;
		} else if (square[i][0].state == 2 && square[i][1].state == 2 && square[i][2].state == 2 ) {
			return -1;
		}
	}
	// 縦のライン
	for( i=0; i<M; i++){
		if (square[0][i].state == 1 && square[1][i].state == 1 && square[2][i].state == 1 ) {
			return 1;
		} else if (square[0][i].state == 2 && square[1][i].state == 2 && square[2][i].state == 2 ) {
			return -1;
		}
	}
	//斜めのライン1
	if (square[0][0].state == 1 && square[1][1].state == 1 && square[2][2].state == 1 ) {
		return 1;
	} else if (square[0][0].state == 2 && square[1][1].state == 2 && square[2][2].state == 2 ) {
		return -1;
	}
	//斜めのライン2
	if (square[0][2].state == 1 && square[1][1].state == 1 && square[2][0].state == 1 ) {
		return 1;
	} else if (square[0][2].state == 2 && square[1][1].state == 2 && square[2][0].state == 2 ) {
		return -1;
	}
	//何もそろっていない。
	return 0;
}

//square の初期化
void InitialBoard(tagSQUARE square[N][M]) {
	int i, j;
	for (i = 0; i < N; i++) {
		for (j = 0; j < M; j++) {
			square[i][j].state = 0;
		}
	}
}
void Input(tagSQUARE square[N][M], int player) {
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
		if (tate > N || tate <= 0 ) {
			printf("error!:1~3の数字で入力してください。\n");
			flag = 1;
		} else if (yoko > M || yoko <= 0 ) {
			printf("error!:1~3の数字で入力してください。\n");
			flag = 1;
		} else if (square[tate-1][yoko-1].state != 0){
			printf("error!:そのマスは埋まっています。\n");
			flag = 1;
		}

	} while (flag);

	square[tate-1][yoko-1].state = player;
}

