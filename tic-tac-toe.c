/***********************************************/
/* @Title: Tic-Tac-Toe.c                       */
/*---------------------------------------------*/
/* @Auther: KenTOKURA                          */
/* @e-mail: s16c1089vn@s.chibakoudai.jp        */
/*---------------------------------------------*/
/* @Description:                               */
/*  M×Nの盤でK目並べをする。                   */
/*  AIは○, Userは×で表す。                     */
/*---------------------------------------------*/
/* @version:1.00 (2019/07/19)                  */
/*  Create 3×3 game for PvP.                   */ 
/* @version:1.10 (2019/07/20)                  */
/*  Create Graphic of play Board.              */ 
/* @version:1.20 (2019/07/20)                  */
/*  Update Graphic to color.                   */ 
/* @version:1.30 (2019/07/20)                  */
/*  Create AI play thinking nothing and randam.*/
/* @version:1.40 (2019/07/20)                  */
/*  Create AI play search center square.       */
/* @version:1.41 (2019/07/21)                  */
/*  Update AI hide miss choice.                */
/* @version:1.42 (2019/07/21)                  */
/*  Change first player choise to random.      */
/* @version:1.50 (2019/07/21)                  */
/*  Create evaluation function initialize.     */
/* @version:1.51 (2019/07/21)                  */
/*  Create AI use evaluation function for play.*/
/* @version:1.60 (2019/07/23)                  */
/*  Create evaluation function everytime.      */
/***********************************************/
#include <unistd.h> //sleep関数
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h> //注意...コンパイル時に-lmをつけること
#define M 3 
#define N 3 //M×N盤条件
#define K 3 //勝利条件

//マスの構造体
typedef struct tagSQUARE {
	int state; //状態... 0:空, 1:○, -1:×.
    int AI_value; //AIから見たそのマスの価値
    int User_value; //Userから見たそのマスの価値
} tagSQUARE;

int InitialBoard( tagSQUARE [M][N] ); //ボードの初期化
int Input( tagSQUARE [M][N], int ); //入力 
int PrintBoard( tagSQUARE [M][N] );  //ボードの状態の出力
int SearchWinner( tagSQUARE [M][N] ); //勝敗チェック
void PrintResult( int ); //結果の出力

int evaluation( int overfield, int cnt_AI, int cnt_user, int cnt_void ); //評価テーブル
int EvaluateSquare( tagSQUARE [M][N], int i, int j ); //一つのマスの評価を更新
void UpdateEvaluate( tagSQUARE [M][N] );// 全てのマスの評価を更新
int AI_Input( tagSQUARE [M][N], int ); //AIの入力 

int main(void) 
{
	int i, j;
	int turn;
    int player; //AI:1, User:-1.
	tagSQUARE square[M][N]; //M×Nの盤 

	printf("Tic-Tac-Toe start!\n");

	//ボードの生成
	InitialBoard(square); //ボードの初期化
    //UpdateEvaluate(square); //評価関数の生成
    printf("Create %d×%d board.\n\n", M, N);
	PrintBoard(square);

	//プレイ
    turn = 1;
    //先攻後攻を決める。
    //-1か1でplayerを初期化
    srand( (unsigned)time( NULL ) ); //srandの初期化
    player = (int)pow( -1, rand()%2+1 );
	while ( SearchWinner( square ) == 0 ) { 
        //更新結果を表示
        /*
        UpdateEvaluate( square ); //評価関数の更新
        printf("||\n");
        printf("||evaluation changed. \n");
        printf("\\/\n\n");
		PrintBoard( square );
        */
        player *= -1;
		printf("\nturn %d.\n", turn ); 
        //printf("player = %d\n",player); //debug用,playerを確認
        UpdateEvaluate(square); //評価関数の更新
        if (player < 0) {
            Input( square, player );
        } else {
            AI_Input( square, player );
        }
		PrintBoard( square );
		if ( turn >= M *N ) break; //全部おいたらloopを抜ける
		turn++;
	}
    //結果の出力
    PrintResult( SearchWinner(square) ); 

	return 0;
}	

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
    sleep(4);//4秒休止

    printf("tate: %d\n", tate );
    printf("yoko: %d\n", yoko );

    square[tate-1][yoko-1].state = player; //選択したマスにプレイヤーを入力

    return 0;
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
