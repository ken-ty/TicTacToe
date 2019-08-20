#include <stdio.h>
#include "tic.h"

//ボードの状態を出力する。
int PrintBoard(tagSQUARE square[M][N]) {
	int i, j;
	for (i = 0; i < M; i++) {
		printf("%2d | ", i+1); //横ライン番号
		for (j = 0; j < N; j++) {
            //printf("%04d", square[i][j].AI_value); //評価関数を表示
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