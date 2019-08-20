#include <stdio.h>
#include "tic.h"

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