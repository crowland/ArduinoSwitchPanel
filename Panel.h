#include <avr/io.h>

#ifndef panel_h
#define panel_h

#define BSP_TICKS_PER_SEC 100

#define TICK_DIVIDER       ((F_CPU / BSP_TICKS_PER_SEC / 1024) - 1)

#define LCD_CS A3    // Chip Select goes to Analog 3
#define LCD_CD A2    // Command/Data goes to Analog 2
#define LCD_WR A1    // LCD Write goes to Analog 1
#define LCD_RD A0    // LCD Read goes to Analog 0
#define LCD_RESET PC6

#define ANALOG_PORT PORTC
#define DIGITAL_PORT1 PORTD
#define DIGITAL_PORT2 PORTB

#define YP_BIT  3
#define XM_BIT  2
#define YM_BIT  1
#define XP_BIT  0

#define YP_PIN  A3
#define XM_PIN  A2
#define YM_PIN  9
#define XP_PIN  8

#define	BLACK           0x0000
#define	BLUE            0x001F
#define	RED             0xF800
#define	GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0 
#define WHITE           0xFFFF

#if TICK_DIVIDER > 255
#   error BSP_TICKS_PER_SEC too small
#elif TICK_DIVIDER < 2
#   error BSP_TICKS_PER_SEC too large
#endif



enum
{
  SWITCH_WIDTH = 40,
  SWITCH_HEIGHT = 30,
  NUM_SWITCHES = 6
};

enum SwitchOne
{
  SWITCH_ONE_NUM = 0,
  SWITCH_ONE_X_POS = 10,
  SWITCH_ONE_Y_POS = 0,
  SWITCH_ONE_PIN = 2
};

enum SwitchTwo
{
  SWITCH_TWO_NUM = 1,
  SWITCH_TWO_X_POS = 130,
  SWITCH_TWO_Y_POS = 0,
  SWITCH_TWO_PIN = 3
};

enum SwitchThree
{
  SWITCH_THREE_NUM = 2,
  SWITCH_THREE_X_POS = 10,
  SWITCH_THREE_Y_POS = 110,
  SWITCH_THREE_PIN = 4
};

enum SwitchFour
{
  SWITCH_FOUR_NUM = 3,
  SWITCH_FOUR_X_POS = 130,
  SWITCH_FOUR_Y_POS = 110,
  SWITCH_FOUR_PIN = 5
};

enum SwitchFive
{
  SWITCH_FIVE_NUM = 4,
  SWITCH_FIVE_X_POS = 10,
  SWITCH_FIVE_Y_POS = 220,
  SWITCH_FIVE_PIN = 4
};

enum SwitchSix
{
  SWITCH_SIX_NUM = 5,
  SWITCH_SIX_X_POS = 130,
  SWITCH_SIX_Y_POS = 220,
  SWITCH_SIX_PIN = 5
};

struct SwitchPressEvent
{
  int xPos;
  int yPos;
};

#endif
