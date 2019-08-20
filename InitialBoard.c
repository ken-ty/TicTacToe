#include "tic.h"

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
