# TicTacToe
3目並べをAIと対戦できます。 コンソールで動きます。    
Create AI play tic-tac-toe.    
![demo](https://github.com/kentokura/TicTacToe/blob/media/gif/demo.gif)
  
使い方
------
### ダウンロード
tic-tac-toe.cをダウンロードしてください。  

### コンパイル
tic-tac-toe.cがあるディレクトリで、以下のコマンドを入力してください。  

gcc tic-tac-toe.c -lm -o tic-tac-toe
  
すると、tic-tac-toe というファイルが作成されたはずです。  
実行するには、以下のコマンドを入力してください。  

./tic-tac-toe
  
解説
----------------
AIはマスごとに、そのマスの現在の価値を計算しています。
その時一番大きな価値をもつマスに打ちます。  
  
tic-tac-toe.cのソースコードに、PrintBoard関数が定義されています。
評価値を出力するコードをコメントアウトしてあるので、興味のある方は見てみてください。  

関連情報
--------
特になし
  
ライセンス
----------
Copyright &copy; 2019 xxxxxx  
ライセンスについては、勉強不足なので、更新予定とします。  
