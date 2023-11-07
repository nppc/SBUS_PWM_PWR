#include "main.h"
#include "button.h"

// call this before going to powerdown mode
void set_button_powerdown(void){
  // Power down: BUTA = 1 (open drain), BUTB = 0
  P1MDOUT &= ~P1MDOUT_B1__BMASK; // Open-drain
  PIN_BUTB = 0;
  PIN_BUTA = 1;
}

// call this after we decided to turn on the power
void set_button_active(void){
  // Active: BUTA = 0, BUTB = 1
  PIN_BUTA = 0;
  PIN_BUTB = 1;
  P1MDOUT |= P1MDOUT_B1__PUSH_PULL;
}
