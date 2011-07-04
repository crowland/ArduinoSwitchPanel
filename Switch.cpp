#include "Switch.h"
#include "Panel.h"
#include <wiring_private.h>

//local switch array
static Switch l_switches[NUM_SWITCHES];

static int switchCount;

char* switchNames[] = 
{"NAV", "STRB", "LNDG", "INT", "TAXI", "T CAM"};

//global active object switches
Switch * const switches[NUM_SWITCHES] = 
{
    &l_switches[0],
    &l_switches[1],
    &l_switches[2],
    &l_switches[3],
    &l_switches[4],
    &l_switches[5]
};

Switch::Switch()
{   
  Switch::initial(this);
}

void Switch::initial(Switch *me)
{
  me->statePtr = &Switch::off;
  me->myState = OFF;
  me->myNum=switchCount++;
   
  switch (me->myNum)
  {
    case 0:      
      me->xPos = SWITCH_ONE_X_POS;
      me->yPos = SWITCH_ONE_Y_POS;
      me->myName = switchNames[SWITCH_ONE_NUM];
      me->myPin = SWITCH_ONE_PIN;
      break;
  
    case 1:
      me->xPos = SWITCH_TWO_X_POS;
      me->yPos = SWITCH_TWO_Y_POS;
      me->myName = switchNames[SWITCH_TWO_NUM];
      me->myPin = SWITCH_TWO_PIN;
      break;
  
    case 2:
      me->xPos = SWITCH_THREE_X_POS;
      me->yPos = SWITCH_THREE_Y_POS;
      me->myName = switchNames[SWITCH_THREE_NUM];
      me->myPin = SWITCH_THREE_PIN;
      break;
  
    case 3:
      me->xPos = SWITCH_FOUR_X_POS;
      me->yPos = SWITCH_FOUR_Y_POS;
      me->myName = switchNames[SWITCH_FOUR_NUM];
      me->myPin = SWITCH_FOUR_PIN;
      break;
  
    case 4:
      me->xPos = SWITCH_FIVE_X_POS;
      me->yPos = SWITCH_FIVE_Y_POS;
      me->myName = switchNames[SWITCH_FIVE_NUM];
      me->myPin = SWITCH_FIVE_PIN;
      break;
  
    case 5:
      me->xPos = SWITCH_SIX_X_POS;
      me->yPos = SWITCH_SIX_Y_POS;
      me->myName = switchNames[SWITCH_SIX_NUM];
      me->myPin = SWITCH_SIX_PIN;
      break;
   }
}

void Switch::off(Switch *me)
{  
  if (me->myNum > 3)  
    bitSet(ANALOG_PORT, me->myPin);
  else
    bitSet(DIGITAL_PORT2, me->myPin);
  
  me->statePtr = &Switch::on;
  me->myState = ON;
}
  
void Switch::on(Switch *me)
{  
  if (me->myNum > 3)  
    bitClear(ANALOG_PORT, me->myPin);
  else
    bitClear(DIGITAL_PORT2, me->myPin);
    
  me->statePtr = &Switch::off;
  me->myState = OFF;
}

char* Switch::getState()
{
  return myState;
}

void Switch::execute()
{
  statePtr(this);
}
