# TicTacToe
3目並べをAIと対戦できます。 コンソールで動きます。    
Create AI play tic-tac-toe.    
![demo](https://github.com/kentokura/TicTacToe/blob/media/gif/demo.gif)
  
使い方
------
### ダウンロード
全てのファイルをダウンロードしてください。  

### コンパイル
以下のコマンドを入力してください。  

~~gcc tic-tac-toe.c -lm -o tic-tac-toe~~  
gcc main.c EvaluateSquare.c InitialBoard.c Input.c UpdateEvaluate.c PrintBoard.c PrintResult.c SearchWinner.c AI_Input.c evaluation.c -o game

  
すると、gameという実行ファイルが作成されたはずです。  
実行するには、以下のコマンドを入力してください。  

~~./tic-tac-toe~~  
./game
  
解説
-------
~~AIはマスごとに、そのマスの現在の価値を計算しています。
その時一番大きな価値をもつマスに打ちます。  ~~
  
~~tic-tac-toe.cのソースコードに、PrintBoard関数が定義されています。
評価値を出力するコードをコメントアウトしてあるので、興味のある方は見てみてください。~~

(2019/08/20)追記: ファイルを分割したので、適宜読み替えてください。
### ソースコードの変更の仕方
![demo](https://github.com/kentokura/TicTacToe/blob/media/gif/demo2.gif)

関連情報
--------
###バージョン情報
````
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
/* @version:1.70 (2019/08/20)                  */
/*  Separate file.                             */
/***********************************************/
````
  
ライセンス
----------
Copyright &copy; 2019 xxxxxx  
ライセンスについては、勉強不足なので、更新予定とします。  
