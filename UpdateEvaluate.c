#include "tic.h"
//評価関数の更新
void UpdateEvaluate(tagSQUARE square[M][N]) {
	int i, j;
	for (i = 0; i < M; i++) {
		for (j = 0; j < N; j++) {
            //square[i][j].AI_valueを更新する関数
            square[i][j].AI_value = EvaluateSquare(square, i, j);
        }
    }
}