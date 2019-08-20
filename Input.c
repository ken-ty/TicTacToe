#include "tic.h"
#include <stdio.h>

/*
プレイヤーの入力
ボードとプレイヤーを引数にとり、
関数内でプレイヤーが入力したマスにプレイヤーの数字を入れる。
*/

int Input(tagSQUARE square[M][N], int player) {
	int tate, yoko;
	int flag; //異常入力検知

    printf(" User turn, Where is put?\n");
	do {
		flag = 0;
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