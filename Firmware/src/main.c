//#pragma src
//-----------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------
#include "main.h"
#include "InitDevice.h"
#include "sbus.h"
#include "button.h"
#include "adc.h"

#define BUT_SENS_HIGH (CMP1CN0 & CMP1CN0_CPOUT__POS_GREATER_THAN_NEG)

volatile U16_U8 pwm_channels[4];
//volatile bit startup_reset;
volatile bit PWM_started = false;
volatile uint8_t delay_powering_counter;
volatile uint8_t led_pattern = 0, led_pattern_counter = 0;
// 0 - led off: Module is not powered
// 1 - led on: Module is powered
// 2 - fast blink: Module is in startup/shutdown process
// 3 - slow blink: After starting up indicates a low battery

volatile uint16_t timeout_counter = 0;
volatile bit timeout_tick = false;

//-----------------------------------------------------------------------------
// SiLabs_Startup() Routine
// ----------------------------------------------------------------------------
// This function is called immediately after reset, before the initialization
// code is run in SILABS_STARTUP.A51 (which runs before main() ). This is a
// useful place to disable the watchdog timer, which is enable by default
// and may trigger before main() in some instances.
//-----------------------------------------------------------------------------
void SiLabs_Startup(void) {

}

//-----------------------------------------------------------------------------
// main() Routine
// ----------------------------------------------------------------------------
int main(void) {

  enter_DefaultMode_from_RESET();

  PIN_MOSFET = false; // turn power mosfet off

  ADC0CN0_ADBUSY = true; // Start first conversion

  // PWM is disabled.

  IE_EA = true; //Enable interrupts

  // we wait for button to be pressed for at least 2 sec to ensure this is intended power on.
  led_pattern = 2; // fast blink
  delay_powering_counter = 0;
  while(delay_powering_counter<125){
      //if (BUT_SENS_HIGH && delay_powering_counter>50) goPowerDown(); // if button released too early
      PCON0 |= PCON0_CPUIDLE__BMASK; // go to IDLE
      PCON0 = PCON0; // ... followed by a 3-cycle dummy instruction
  }

  led_pattern = 1; // LED ON
  while(!BUT_SENS_HIGH); // wait until button is released
  waitNms(100); // wait for debounce

  PIN_MOSFET = true; // turn on power mosfet

  set_button_active();
  // now button behavior is reversed
  waitNms(100); // wait for new button levels stabilize

  while(1){
      // Power down if button pressed
      if(BUT_SENS_HIGH) { // Power button is pressed
          if(led_pattern != 2){
              led_pattern = 2; // fast blink
              delay_powering_counter = 0; // start counter for power off
          }
          if (delay_powering_counter>125) {
              led_pattern = 0; // LED OFF
              while(BUT_SENS_HIGH); // wait until button is released
              waitNms(100);
              goPowerDown(); // go power down
          }
      }else if(led_pattern == 2) led_pattern = 1; // restore led pattern

      if(sbus_packet_received){
          // check pack validity (secondary check)
          uint8_t tmp = sbus_packet[0];
          sbus_packet_received = false;
          if(sbus_parse()){
              // packet is well received
              uint16_t tmp;
              timeout_counter = 0;
              // convert sbus data to PWM and map channels to output
              tmp = convert_sbus_2_pwm(sbus_ch[1]);
              IE_EA = false;
              pwm_channels[0].u16 = tmp;
              IE_EA = true;
              tmp = convert_sbus_2_pwm(sbus_ch[2]);
              IE_EA = false;
              pwm_channels[1].u16 = tmp;
              IE_EA = true;
              tmp = convert_sbus_2_pwm(sbus_ch[3]);
              IE_EA = false;
              pwm_channels[2].u16 = tmp;
              IE_EA = true;
              tmp = convert_sbus_2_pwm(sbus_ch[0]);
              IE_EA = false;
              pwm_channels[3].u16 = tmp;
              IE_EA = true;

              if(!PWM_started){
                  PWM_started = true;
                  PCA0POL = PCA0POL_CEX0POL__INVERT | PCA0POL_CEX1POL__INVERT;
              }
          }
      }

      // check for timeout
      if(timeout_tick){
          timeout_tick = false;
          timeout_counter++;
          if(timeout_counter>3760){ // about 60 seconds
              // going power down due to no signal from transmitter
              led_pattern = 2; // fast blink
              delay_powering_counter = 0;
              while(delay_powering_counter < 50);
              goPowerDown();
          }
      }

      // check voltage
      if(isVoltageLow() && led_pattern !=2) led_pattern = 3;
  }

}
