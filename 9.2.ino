#include <LiquidCrystal.h>

LiquidCrystal lcd(1,2,3,4,5,6);

byte Dino[3][8] = {
{
0b00111,
0b00101,
0b00111,
0b00110,
0b01111,
0b11110,
0b01010,
0b01010
},
{
0b00111,
0b00101,
0b00111,
0b00110,
0b01111,
0b11110,
0b01010,
0b10010
},
{
0b00111,
0b00101,
0b00111,
0b00110,
0b01111,
0b11110,
0b01010,
0b01001
}
};

byte DinoJump[8]=
{
0b00111,
0b00101,
0b00111,
0b00110,
0b01111,
0b11110,
0b01001,
0b10010
};

byte kaktus[8] = {
0b00000,
0b00101,
0b00111,
0b00001,
0b00101,
0b10111,
0b11100,
0b00100
};
int Score=1;
byte kaktusPos=15; //Позиция кактуса по x
byte DinoPos=1;//Позиция дино по y
bool death=false; // умер ли персонаж
byte jumpDurance; // длительность прыжка
bool isJump=false; //прыгнул ли персонаж
bool Play=false;

void setup() {
pinMode(13,INPUT); //реализуем кнопку
lcd.begin(16, 2); // размер экрана

lcd.createChar(1, kaktus); // -//- под названием 1

}

void loop() {
if(Play){
lcd.clear(); //очистить весь экран
if(!death) Alive(); //если жив
else Death(); //если мертв
delay(((10000/Score)/200)+50); //Ограничение по fps
}
else{
Display(1);
if(digitalRead(13)) Play=true;
}
}

void Death(){
Display(3);
  if(digitalRead(13)){ death=false; kaktusPos=15; Score=0;}//если нажать кнопку, перезапуск
}

void Alive(){
lcd.createChar(0, Dino[Score%3]); //выделяем память в дисплее под динозаврика впод названием 0
//если нажали кнопку и динозаврик еще не в полете
if (digitalRead(13) & !isJump){
jumpDurance=0; //обнулить длину прыжка
isJump=true; //начать прыжок
}

Display(2);

//если прыгнул
if(isJump) Jump();
lcd.createChar(0,DinoJump);
kaktusPos--; //перемещаем кактус левее
if (kaktusPos>100) kaktusPos=15; //если положение кактуса левее края экрана, отправить его в правый угол
if (kaktusPos==1 & DinoPos==1) death=true;//если кактус касается дино, наступает смерть
}


void Jump(){
DinoPos=0;//поднять дино вверх
jumpDurance++;//увеличивать длительность

//если дительность больше
if(jumpDurance==4)
{DinoPos=1; //опустить дино
isJump=false;}// отключить прыжок
}


void Display(int choice)
{
switch(choice){
case 1:
lcd.setCursor(2,0);
lcd.print("Press button");
lcd.setCursor(4,1);
lcd.print("to play!");
break;
case 2:
//рисуем дино в координатах 1,DinoPos
lcd.setCursor(1, DinoPos);
lcd.write(byte(0));
//рисуем кактус в координатах kaktusPos,1
lcd.setCursor(kaktusPos, 1);
lcd.write(byte(1));

Score++;//прибавить к счету 1
lcd.setCursor(6,0);
lcd.print("Score:");
lcd.print(Score);
break;
case 3:
lcd.setCursor(3, 0);//оступ 3 клетки
lcd.print("Game Over!"); //если смерть, написать GameOver
lcd.setCursor(3,1);
lcd.print("Score:");
lcd.print(Score);
break;
}}
