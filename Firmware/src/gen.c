#include "main.h"
#include "button.h"
#include "adc.h"

#define LOW_BATTERY_VOLTAGE 3400
uint8_t low_volt_counter = 0;

void waitNms(uint16_t ms){
  // convert ms to timer ticks
  // 1tick of PCA0 at div4 = 0.08163265us
  // 1ms = 49000 timer ticks (H register = 48)
  // we can use PCA timer ticks as it runs always with SYSCK/4 speed
  // lets use only PCA0H to make it easier to work with 16bit registers of timer that we can't pause
  uint8_t tmp,tmp1;
  while(ms!=0){
    tmp = PCA0L; // we need to read first PCA0L to latch PCA0H
    tmp = PCA0H;
    tmp+=48;
      while(1){
        tmp1 = PCA0L; // we need to read first PCA0L to latch PCA0H
        tmp1 = PCA0H;
        if(tmp1 == tmp){break;}
    }
    ms--;
  }
}

uint16_t convert_sbus_2_pwm(uint16_t val){
// ErSky9X pwm range for -125% 0 125% in us: 860-1500-2140
// SBus range for these numbers is somehow not very symmetric:
// 0 - 992 - 2014 (lower range is 992, higher range is 1022).
// Scale numbers are 0.645161 and 0.626223 respectively.
// Average scaling value is 0.63569.
// The coefficient 6.125 is for PCA0/PWM0 counter value.

//  uint16_t us = (uint16_t)((float)val * 0.63569) + 860;
//  return (uint16_t)((float)us * 6.125);
// Reduce one multiplication:
  return (uint16_t)((float)val * 3.8936) + 5267;
}

void goPowerDown(void){
  // turn off pwm
  IE_EA = 0; //diasble interrupts
  PCA0CPL0 = 0x00;
  PCA0CPH0 = 0x00;
  PCA0CPL1 = 0x00;
  PCA0CPH1 = 0x00;
  SFRPAGE = 0x10;
  PWMCPUDL0 = 0x00;
  PWMCPUDH0 = 0x00;
  PWMCPUDL1 = 0x00;
  PWMCPUDH1 = 0x00;
  SFRPAGE = 0x00;
  waitNms(20); // wait for pwm to update
  PCA0POL = 0;
  PIN_MOSFET = false; // turn mosfet off
  set_button_powerdown();
  led_pattern = 0; // LED OFF
  waitNms(200); // just in case to not brick the device
  // going to shutdown
  REG0CN = REG0CN_STOPCF__SHUTDOWN;
  PCON0 = PCON0_CPUSTOP__BMASK;
}

// new voltage reading comes every 16ms.
// For half a second it will be 31 (500/16)
bit isVoltageLow(void){
  bit retval = false;
  uint16_t volt = readVoltage();
  if(volt !=0){
      if(volt <= LOW_BATTERY_VOLTAGE){
        low_volt_counter++;
        if(low_volt_counter > 31) retval = true;
      }else{
          low_volt_counter = 0;
      }
  }
  return retval;
}
