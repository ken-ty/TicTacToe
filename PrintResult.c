#include <stdio.h>
#include "tic.h"
//引数winnerに応じて結果の出力をする。
void PrintResult( int winner ) {
    //AIの勝ち
    if ( winner == 1 ) {
        printf("\x1b[31m");
        printf("\nAI");
        printf("\x1b[39m");
        printf(" wins!\n");
    }
    //Userの勝ち//user
    if ( winner == -1 ) {
        printf("\x1b[34m");
        printf("\nUser");
        printf("\x1b[39m");
        printf(" win!\n");
    }
    //引き分け
    if ( winner == 0) {
        printf("\nDraw Game.\n");
    }
}