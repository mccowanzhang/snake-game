/*
  Snake Game using Arduino
  by: McCowan Zhang
*/

#include "U8glib.h" //library for oled

U8GLIB_SSD1306_128X64 oled(10, 9, 13, 11, 12); // constructor for the particular OLED, defines pins for oled

//set up pin definition
//the buttons are send digital signals
int upButton = 2;
int downButton = 3;
int leftButton = 4;
int rightButton = 5;

//define variables
int snakeDir = 0;
int foodx = 30;
int foody = 30;
int snakex = 50;
int snakey = 50;



//set up the pin mode - all of the buttons recieve input
void setup() {
  pinMode(upButton, INPUT_PULLUP);
  pinMode(downButton, INPUT_PULLUP);
  pinMode(leftButton, INPUT_PULLUP);
  pinMode(rightButton, INPUT_PULLUP);
}
//void U8G2::drawFrame(snakex, snakey, 5, 5);

void loop() {
  oled.firstPage();
  do{
  oled.drawBox(snakex, snakey, 5, 5);
  oled.drawCircle(foodx, foody, 1);
  //  u8g.drawFilledEllipse(foodx, foody, 1)
  //  u8g.drawBox(snakex, snakey, 5, 5);


  if(snakeDir == 1){
    snakey--;
    snakex = snakex;
  }
  if(snakeDir == 2){
    snakey++;
    snakex = snakex;
  }
  if(snakeDir == 3){
    snakex--;
    snakey = snakey;
  }
  if(snakeDir == 4){
    snakex++;
    snakey = snakey;  
  }
  

  
  //change the state of the snakes direction when each button is pressed
  if (digitalRead(upButton)== HIGH) {
    snakeDir = 1;
  }
  if (digitalRead(downButton)== HIGH) {
    snakeDir = 2;
  }
  if (digitalRead(leftButton)== HIGH) {
    snakeDir = 3;
  }
  if (digitalRead(rightButton)== HIGH) {
    snakeDir = 4;
  }
  


  //switch between different states of the direction that the snake head is going

  /*
  switch (snakeDir) {
    case 1:
      snakey = snakey - 1;
      break;
    case 2:
      snakey = snakey + 1;
      break;
    case 3:
      snakex = snakex - 1;
      break;
    case 4:
      snakex = snakex + 1;
      break;
  }
  */

 
}
while(oled.nextPage());
}
