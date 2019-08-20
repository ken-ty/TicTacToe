#include "tic.h"

//square[i][j].valueを更新する関数
int EvaluateSquare(tagSQUARE square[M][N], int i,int j) {
    int k, l;
    int cnt_AI, cnt_User, cnt_void;
    int overfield;
    int direction;
    int value = 0;
    int A;
    int I, J;
    int cnt = 0;
    if (square[i][j].state == 0) {
        //printf("\nevaluate square[%d][%d] ...\n",i,j);
        for (direction = 1; direction <= 4; direction++) { //4方向
            //printf("direction%d\n",direction);
            for (k = 0; k < K; k++) {//長さ3のラインを3通り
                cnt_AI =0;
                cnt_User =0;
                cnt_void =0;
                overfield = 0;
                //全てのラインを検索し、valueに評価の合計を与える
                for (l = 0; l < K; l++) { //１マスずつ見る。
                    //1マスずつ状態を確認
                    switch( direction ) {
                        case 1: //横
                            J = (j-2+k)+l;
                            if ( J < 0 || J > N-1 ) {
                                overfield = 1;
                            } else {
                                A = square[i][J].state;
                            }
                            break;
                        case 2: //縦
                            I = (i-2+k)+l;
                            if ( I < 0 || I > M-1 ) {
                                overfield = 1;
                            } else {
                                A = square[I][j].state;
                            }
                            break;
                        case 3: //斜め１
                            I = (i-2+k)+l;
                            J = (j-2+k)+l;
                            if ( I < 0 || I > M-1 ) {
                                overfield = 1;
                            }else if ( J < 0 || J > N-1 ) {
                                overfield = 1;
                            } else {
                                A = square[I][J].state;
                            }
                            break;
                        case 4: //斜め2
                            I = (i+2-k)-l;
                            J = (j-2+k)+l;
                            if ( I < 0 || I > M-1 ) {
                                overfield = 1;
                            } else if ( J < 0 || J > N-1 ) {
                                overfield = 1;
                            } else {
                                A = square[I][J].state;
                            }
                            break;
                    }
                    //カウント
                    switch( A ) {
                        case -1:
                            cnt_User++;
                            break;
                        case 0:
                            cnt_void++;
                            break;
                        case 1:
                            cnt_AI++;
                            break;
                    }
                }
                //カウントしたパターンによって、評価を加算する
                value += evaluation( overfield, cnt_AI, cnt_User, cnt_void );
            }
        }
    }
    return value;
}