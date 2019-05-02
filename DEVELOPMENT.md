yes
Split Pong game into 3 classes
* Gameboard where all events take place
* PongObject(int x, int y)
  * for sizing of each paddle and a ball

 4/28/19
  * Split PongObject into Ball and Paddle
  * Move Gameboard functionality into ofApp
  * Work on draw functions and update logic

 4/30/19
  * redownloaded openFrameworks to fix file structure

05/01/19
  * created entirely new project to fix LNK1168 error. paddles, ball, and drawings finally showing up
  * worked on collision logic, finalizing on finding intersection of ball movement vector and paddle length
    * originally, had just looked at coordinate position but incredibly buggy and unreliable
  *
