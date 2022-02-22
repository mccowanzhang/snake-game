#include "U8glib.h"
U8GLIB_SSD1306_128X64 u8g(10, 9, 12, 11, 13);

int leftButton = 5;
int rightButton = 2;
int upButton = 4;
int downButton = 3;

int testNumber = 5;
int x = 60;
int y = 30;
int score = 0;
int level = 1;
int gameSpeed = 50;
int i;
int snakeDir;

const uint8_t snakePattern [] PROGMEM = {
  0xf0,//1111 0000
  0x90,//1001 0000
  0x90,//1001 0000
  0xf0 //1111 0000
};

const uint8_t bugPattern [] PROGMEM = { //8x4 block
  0xAA,//1010 1010
  0xFF,//1111 1111
  0xFF,//1111 1111 
  0x55 //0101 0101
};
const uint8_t foodPattern [] PROGMEM = { //4x4 block
  0x90,//1001 0000
  0x60,//0110 0000 
  0x60,//0110 0000 
  0x90 //1001 0000
};

struct FOOD{
  int x;
  int y;
  int yes;
};
FOOD food = {
  25, 30, 1
};

void setup() {
  pinMode(leftButton, INPUT_PULLUP);
pinMode(rightButton, INPUT_PULLUP);
pinMode(upButton, INPUT_PULLUP);
pinMode(downButton, INPUT_PULLUP);

digitalWrite(leftButton, HIGH);
digitalWrite(rightButton, HIGH);
digitalWrite(upButton, HIGH);
digitalWrite(downButton, HIGH);
}
void foodElement(int x, int y){
  u8g.drawBitmapP(x,y,1,4, foodPattern);
}
void element(int x, int y){
  u8g.drawBitmapP(x,y,1,4,snakePattern);
}
struct SNAKE {
  int x[200];
  int y[200];
  int node;
  int dir;
  int lefe;
};
SNAKE snake = {
  {24,24}, {30,30}, 8, rightButton, 0
};
void draw(){
  testNumber = random(1,100);
  x = 5*random(2, 24);
  y = 7*random(1, 7);
  u8g.setFont(u8g_font_5x7);
  u8g.setPrintPos(110, 10);
  u8g.print(x);
  u8g.setPrintPos(110, 20);
  u8g.print(y);
  u8g.setPrintPos(x,y);
  u8g.print(testNumber);
  delay(1000);
}
void drawFood(){
  x = 4*random(2,23);
  y = 4*random(2, 14);
  foodElement(x,y); 
}
void printScore(int x, int y, int s) {
  u8g.setFont(u8g_font_6x10);
  u8g.setPrintPos(x,y);
  u8g.print(s);
}
void ui(){
  u8g.drawFrame(4,4,96,56);
  u8g.drawFrame(2,2,100,60);
  u8g.setFont(u8g_font_5x7);
  u8g.drawStr(104,12, "LEVEL");
  u8g.drawStr(104,40, "SCORE");
}
void key(){
  if(digitalRead(leftButton) == LOW){
    snakeDir = 1;
  }
  if(digitalRead(rightButton) == LOW){
    snakeDir = 2;
  }
  if(digitalRead(upButton) == LOW){
    snakeDir = 3;
  }
  if(digitalRead(downButton) == LOW){
    snakeDir = 4;
  }
}

void snakeGame(){
  switch(snakeDir){
    case 1:
    snake.x[0] -= 1;
           if(snake.x[0]<=3) {
             snake.x[0] = 96;
           } break;
    case 2:
    snake.x[0] += 1;
           if(snake.x[0]>=96) {
             snake.x[0] = 5;
           } break;
    case 3:
    snake.y[0] -= 1;
          if(snake.y[0]<=3) {
            snake.y[0] = 55;
          } break;
    case 4:
    snake.y[0] += 1;
          if(snake.y[0]>=58) {
            snake.y[0] = 4;
          } break;
  }

if((snake.x[0]==x)&&(snake.y[0]==y)) {
    //snake.node++;
    //food.yes = 1;
    score += 1;
    level = score/5+1;
    x=4*random(4, 22);
    y=4*random(2, 14);
  }
    for(i=snake.node-1;i>0;i--){
snake.x[i] = snake.x[i-1];
snake.y[i] = snake.y[i-1];
}
}
void loop() {
 // x = 4*random(4,22);  //get random number outside of oled cycle
 // y = 4*random(2,14); 
  
u8g.firstPage();
do{
  ui();
  //draw();
  for(i=0; i<snake.node; i++){
    element(snake.x[i], snake.y[i]);
  }
  foodElement(x,y);
  printScore(109, 22, level);
  printScore(109, 50, score);
}
  while(u8g.nextPage());
  key();
  snakeGame();
  delay(100);
}
