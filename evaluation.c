#include <stdio.h>
#include "tic.h"

int evaluation( int overfield, int cnt_AI, int cnt_User, int cnt_void ) {
    int value = 0;
    if ( !overfield ) {
        if ( cnt_void == 1 && cnt_AI == 2) { //空1, 〇2
            value = 213;
        } else if ( cnt_void == 1 && cnt_User == 2) { //空1, × 2
            value = 73;
        } else if ( cnt_void == 2 && cnt_AI == 1 ) { //空2 , 〇1
            value = 18;
        } else if ( cnt_void == 3) { //空3
            value = 9;
        } else if ( cnt_void == 1 && cnt_AI == 1 && cnt_User == 1) { //空1, 〇1 , × 1
            value = 2;
        } else if ( cnt_void == 2 && cnt_User == 1) { //空2 , × 1
            value = 1;
        }
    }
    return value;
}

/*ラインの評価 以下の表より、valueを返す。
  //3×3のみ対応
    勝利手
    〇2は最も高い。(4×次善策より高い)
    213
    ============================
    相手の勝利手を防ぐ。
    × 2は防ぐ。(4×次善策より高い)
    73
    ============================
    勝利に近づく
    空1, 〇1 (2×次善策より高い)
    18
    空2 (4×次善策より高い)
    9
    ============================
    あんまり意味がない
    ×1,〇1 (2×次善策より高い)
    2
    ×1,から1。
    1
    ============================
    ラインじゃない
    overfield が1以上
    0
*/