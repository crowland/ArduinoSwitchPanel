
#include "Panel.h"


#define ON "ON"
#define OFF "OFF"

class Switch
{
  private:
  
    typedef void (*State)(Switch*);
    int myNum;    
    int myPin;
    State statePtr;
  
  public:
    
    Switch();  
    void execute();
    char* getState();
    
    int xPos;
    int yPos;
    char* myName;
    char* myState;    
    
  private:
         
    static void initial(Switch *me);
    static void off(Switch *me);
    static void on(Switch *me);
};

extern Switch * const switches[NUM_SWITCHES];



