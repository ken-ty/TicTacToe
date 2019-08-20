#include <stdio.h>
#include <unistd.h> //sleep関数
#include "tic.h"

int AI_Input(tagSQUARE square[M][N], int player) {
	int i, j;
	int tate, yoko;
    int value = -1;

    //全てのマスを調べ、最も大きいvalueのマスを見つける
	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
            if (square[i][j].state != 0) { //置かれているマスは無視
            } else if (value < square[i][j].AI_value ) {
                //valueを更新
                value = square[i][j].AI_value;
                //選んだ座標を代入
                tate = i+1;
                yoko = j+1;
            }
		}
	}

    //表示
    //プレイ間を出すため、数秒止める。
    printf(" AI turn, Please wait.\n");
    sleep(3);//3秒休止

    printf("tate: %d\n", tate );
    printf("yoko: %d\n", yoko );

    square[tate-1][yoko-1].state = player; //選択したマスにプレイヤーを入力

    return 0;
}