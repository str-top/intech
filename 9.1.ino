#include <Adafruit_LiquidCrystal.h>
#include <Keypad.h>

const byte rows = 4;

const byte cols = 4;

char keys[rows][cols] = {

{1,2,3,-2},

{4,5,6,'B'},

{7,8,9,-4},

{'*',-1,-3,'D'}

};

byte rowPins[rows] = {11, 10, 9, 8};
byte colPins[cols] = {7, 6, 5, 4};
Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, rows, cols);
Adafruit_LiquidCrystal lcd_1(0);

 int a,b,c,i;
char d;
char key;
char znak=' ';

void setup()
{
  byte G[8] = {
  B01010,
  B11011,
  B11111,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};
  lcd_1.begin(16, 2);
  lcd_1.createChar(2, G);

  pinMode(12, OUTPUT);
  randomSeed(analogRead(0));
  Serial.begin(9600);

  lcd_1.begin(16, 2);
  lcd_1.setCursor(0, 0);
  lcd_1.print("Level=");
  lcd_1.setCursor(6, 0);
  lcd_1.print("0");
  lcd_1.setCursor(8, 0);
  lcd_1.print("Chet=");
  lcd_1.setCursor(14, 0);
  lcd_1.print(0);
}
int chet=0;
int hpi=3;

void hp(int i)
{
  if(i==3)
  {
    lcd_1.setCursor(12, 1);
  	lcd_1.print(char (2));
  	lcd_1.setCursor(13, 1);
  	lcd_1.print(char (2));
  	lcd_1.setCursor(14, 1);
  	lcd_1.print(char (2));
  }
  else if(i==2)
  {
    lcd_1.setCursor(12, 1);
  	lcd_1.print(char (2));
  	lcd_1.setCursor(13, 1);
  	lcd_1.print(char (2));
    lcd_1.setCursor(14, 1);
    lcd_1.print(" ");
  }
  else if(i==1)
  {
    lcd_1.setCursor(12, 1);
  	lcd_1.print(char (2));
    lcd_1.setCursor(13, 1);
  	lcd_1.print(" ");
    lcd_1.setCursor(14, 1);
    lcd_1.print(" ");
  }
  else
  {
    lcd_1.setCursor(12, 1);
  	lcd_1.print(" ");
    lcd_1.setCursor(13, 1);
  	lcd_1.print(" ");
    lcd_1.setCursor(14, 1);
    lcd_1.print(" ");
  }
}
int cht=0;
int slo=cht+2;

void loop()
{
  slo=cht+2;
  if(slo>=6)
  {
   slo=5;
  }
  a=0;
  b=0;
  c=random(1,slo);
  lcd_1.setCursor(0, 1);
  lcd_1.print(a);
  lcd_1.setCursor(3, 1);
  lcd_1.print(b);
  lcd_1.setCursor(5, 1);
  lcd_1.print("=");
  if(c==1)
  {
    a=random(1,100);
  	b=random(1,100);
    d='+';
    i=a+b;
  }
  else if(c==2)
  {
    a=random(1,100);
    b=random(1,100);
    d='-';
  	i=a-b;
  }
  else if(c==3)
  {
    a=random(1,100);
  	b=random(1,100);
    d='*';
    i=a*b;
  }
  else if(c==4)
  {
    a=random(50,100);
  	b=random(1,50);
    d='/';
    i=a/b;
  }
  Serial.println(i);
    lcd_1.setCursor(0, 1);
    lcd_1.print(a);
    lcd_1.setCursor(3, 1);
    lcd_1.print(b);
    lcd_1.setCursor(2, 1);
    lcd_1.print(d);
    lcd_1.setCursor(5, 1);
    lcd_1.print("=");
  hp(hpi);
  int key;
  key=numberes();
  lcd_1.setCursor(6, 1);
  lcd_1.print(key);
  if(i==key)
  {
    hp(hpi);
    if(hpi<3)
    {
      hpi++;
    }
    Serial.println("=");
    chet++;
    digitalWrite(12, 1);
    delay(100);
    digitalWrite(12, 0);
    lcd_1.setCursor(14, 0);
  	lcd_1.print(chet);
    lcd_1.setCursor(7, 1);
  	lcd_1.print("     ");
    if(chet>=3)
    {
      	lcd_1.setCursor(0, 0);
  		lcd_1.print("                ");
      	lcd_1.setCursor(0, 1);
  		lcd_1.print("                ");
        lcd_1.setCursor(5, 0);
  		lcd_1.print("Next level");
      	cht++;
      	chet=0;
      	delay(2000);
      	lcd_1.setCursor(0, 0);
  		lcd_1.print("                ");
      	lcd_1.setCursor(0, 0);
 		lcd_1.print("Level=");
        lcd_1.setCursor(6, 0);
  		lcd_1.print(cht);
  		lcd_1.setCursor(8, 0);
  		lcd_1.print("Chet=");
  		lcd_1.setCursor(14, 0);
  		lcd_1.print(0);
        hpi=3;
    }
  }
  else
  {
    hp(hpi);
    hpi--;
    if(hpi==0)
    {
   	Serial.println("-");
    lcd_1.clear();
    lcd_1.setCursor(7, 0);
  	lcd_1.print("Loser");
    chet=0;
    delay(1000);
    lcd_1.clear();
    lcd_1.setCursor(0, 0);
  	lcd_1.print("Level=");
    lcd_1.setCursor(6, 0);
  	lcd_1.print(cht);
  	lcd_1.setCursor(8, 0);
  	lcd_1.print("Chet=");
  	lcd_1.setCursor(14, 0);
  	lcd_1.print(0);
    cht=0;
    //hpi=3;
    }
  }
  key=0;
  lcd_1.setCursor(6, 1);
  lcd_1.print("    ");
}

byte f=false;
int numberes()
{
  byte ravno=false;
  int key=0;
  int cheslo=0;
  //Serial.println("1");
  byte minus=false;
  int c=0;
  while(c<=6)
  {
    //Serial.println("2");
    while(f==false)
    {
      key = keypad.getKey();
      delay(100);

      if(key)
      {
        f=true;

      }
      //Serial.println(key);
    }
    //Serial.println("4");
    if(key==-2)
  	{
      minus=true;
      key=0;
      cheslo=cheslo*10+key;
      //Serial.println("yes -");
  	}
    if(key==-3)
    {
        key=0;
      	Serial.println("yes =");
      	break;
    }
    if(key==-4)
    {
        key=0;
      	Serial.println("yes c");
      	cheslo=0;
      	c=0;
      	lcd_1.setCursor(7, 1);
  		lcd_1.print("    ");
    }
    if(key!=-1)
    {
    	cheslo=cheslo*10+key;
      	//Serial.println("no 0");
    }
    else if(key==-1)
    {
      	key=0;
      	cheslo=cheslo*10+key;
      	//Serial.println("yes 0");
    }

    lcd_1.setCursor(6, 1);
    lcd_1.print(cheslo);
    key=0;
    f=false;
    c++;
  }

  if(minus==true)
  {
     cheslo=-cheslo;
  }
  //Serial.println("5");
  return cheslo;
}
