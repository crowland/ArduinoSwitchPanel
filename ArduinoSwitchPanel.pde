
#include <TFTLCD.h>
#include "Panel.h"
#include "Queue.h"
#include "Switch.h"

typedef Queue<SwitchPressEvent,10> SwitchPressQueue;
static SwitchPressQueue switchPressQueue;

volatile int pressed = 0;

TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

/*ISR(TIMER2_COMPA_vect)
{  
  int z = readZ();
  
  if (pressed==1 && z <=200)
  {
    pressed = 0;
  }    
  else if (pressed==0 && z>200)
  {
    pressed=1;
    
    int x = readX();
    int y = readY();
    
    Serial.print("X=");Serial.println(x);
    Serial.print("Y=");Serial.println(y);
    
    SwitchPressEvent e;
    e.xPos = x;
    e.yPos = y;
    switchPressQueue.push(e);
  }
}*/

void setup()
{
  delay(1000);
  Serial.begin(9600);
  tft.initDisplay();
  tft.fillScreen(BLACK);
  
  for (int i = 0; i < 6; i++)
    displayInitial(switches[i]); 
  
  /*TCCR2A = ((1 << WGM21) | (0 << WGM20));
  TCCR2B = (( 1 << CS22 ) | ( 1 << CS21 ) | ( 1 << CS20 ));        // 1/2^10
  ASSR &= ~(1<<AS2);
  TIMSK2 = (1 << OCIE2A);
  TCNT2 = 0;
  OCR2A = TICK_DIVIDER;*/
}

int count = 0;
void loop()
{
  if (++count == 10)
  {
    count = 0;  
    while (!switchPressQueue.empty())
    {      
      SwitchPressEvent *e = &switchPressQueue.pop();
      executeSwitch(e->xPos, e->yPos);
      free(e);
    }
  }
  
  int z = readZ();
  
  if (pressed==1 && z <=200)
  {
    pressed = 0;
  }    
  else if (pressed==0 && z>200)
  {
    pressed=1;
    
    int x = readX();
    int y = readY();
    
    Serial.print("X=");Serial.println(x);
    Serial.print("Y=");Serial.println(y);
    
    SwitchPressEvent e;
    e.xPos = x;
    e.yPos = y;
    switchPressQueue.push(e);
  }
  
  pinMode(XM_PIN, OUTPUT);
  pinMode(YP_PIN, OUTPUT);
  pinMode(XP_PIN, OUTPUT);
  pinMode(YM_PIN, OUTPUT);
  
  
  /*if (count%2 > 0) 
    tft.drawRect(10, 10, 100, 100, GREEN);
  else
     tft.drawRect(10, 10, 100, 100, RED); */ 
    
  delay(10);
}

int readZ()
{
  pinMode(XM_PIN, INPUT);
  pinMode(YP_PIN, INPUT);
  pinMode(XP_PIN, OUTPUT);
  pinMode(YM_PIN, OUTPUT);
  
  bitSet(DIGITAL_PORT2, XP_BIT);
  bitClear(DIGITAL_PORT2, YM_BIT);
  bitClear(ANALOG_PORT, XM_BIT);
  bitClear(ANALOG_PORT, YP_BIT);
    
  int z1 = analogRead(XM_PIN); 
  int z2 = analogRead(YP_PIN);
  
  int pressure = (1023-(z1-z2));
  return pressure;
}

int readX() 
{
   pinMode(YP_PIN, INPUT);
   pinMode(YM_PIN, INPUT);   
   pinMode(XP_PIN, OUTPUT);
   pinMode(XM_PIN, OUTPUT);
   delay(5);
   
   bitClear(ANALOG_PORT, YP_BIT);
   bitClear(DIGITAL_PORT2, YM_BIT);
   bitSet(DIGITAL_PORT2, XP_BIT);
   bitClear(ANALOG_PORT, XM_BIT);
   
   int x1 = analogRead(YP_PIN);
   int x2 = analogRead(YP_PIN);
   return x2;
   /*if (x1 == x2)
     return x1;
   else
     return 0;*/
}


int readY() 
{
   pinMode(XP_PIN, INPUT);
   pinMode(XM_PIN, INPUT);   
   pinMode(YP_PIN, OUTPUT);
   pinMode(YM_PIN, OUTPUT);
   delay(5);
   
   bitSet(ANALOG_PORT, YP_BIT);
   bitClear(DIGITAL_PORT2, YM_BIT);
   bitClear(DIGITAL_PORT2, XP_BIT);
   bitClear(ANALOG_PORT, XM_BIT);
   
   int y1 = analogRead(XM_PIN);
   int y2 = analogRead(XM_PIN);
   int y3 = analogRead(XM_PIN);
   Serial.print("y1=");Serial.println(y1);
   Serial.print("y2=");Serial.println(y2);
   Serial.print("y3=");Serial.println(y3);
   return 1023-y2;
   //if (y1 == y2)
     //return 1000-y1;
   //else
     //return return analogRead(XM_PIN);
}

void executeSwitch(int x, int y)
{
  if ((x > 100 && x <= 900) && (y > 70 && y <= 1000))
  {
    if (x <= 450) //column 1
    {
      if (y >= 670) //row 1
      {
        switches[0]->execute();
        displaySwitch(switches[0]);
      }
      else if (y >= 375 && y <= 635)//row 2
      {
        switches[2]->execute();
        displaySwitch(switches[2]);
      }
      else if (y >= 75 && y <= 345)//row 3
      {
        switches[4]->execute();
        displaySwitch(switches[4]);
      }
     }      
     else if (x >= 530) //column 2
     {
       if (y >= 670) //row 1
       {
         switches[1]->execute();
         displaySwitch(switches[1]);
       }
       else if (y >= 375 && y <= 635)//row 2
       {
         switches[3]->execute();
         displaySwitch(switches[3]);
       }
       else if (y >= 75 && y <= 345)//row 3
       {
        switches[5]->execute();
        displaySwitch(switches[5]);
       }
     }
  }  
}

void displaySwitch(Switch *s)
{
  Serial.print(s->myName);
  Serial.print(" : ");
  Serial.println(s->myState);
  
  //tft.drawRect(s->xPos, s->yPos, 100, 100, RED); 
  //tft.drawString(s->xPos+5, s->yPos+5, s->myName, RED, 3);
  //tft.drawString(s->xPos+5, s->yPos+30, "   ", BLACK, 3);
  tft.fillRect(s->xPos+5, s->yPos+5, 90, 90, BLACK);
  
  if (strcmp(s->myState, "ON") == 0)
  {
    tft.drawString(s->xPos+5, s->yPos+5, s->myName, RED, 3);
    tft.drawString(s->xPos+5, s->yPos+30, s->myState, RED, 3);
  }
  else
  {
    tft.drawString(s->xPos+5, s->yPos+5, s->myName, GREEN, 3);
    tft.drawString(s->xPos+5, s->yPos+30, s->myState, GREEN, 3);
  }
}

void displayInitial(Switch *s)
{  
  tft.drawRect(s->xPos, s->yPos, 100, 100, GREEN); 
  tft.drawString(s->xPos+5, s->yPos+5, s->myName, GREEN, 3);
  tft.drawString(s->xPos+5, s->yPos+30, s->myState, GREEN, 3);
}
