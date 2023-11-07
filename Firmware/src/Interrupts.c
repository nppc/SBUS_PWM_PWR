//#pragma src

#include "main.h"
#include "sbus.h"

//-----------------------------------------------------------------------------
// PCA0_ISR
//-----------------------------------------------------------------------------
//
// PCA0 ISR Content goes here. Remember to clear flag bits:
// PCA0CN0::CCF0 (PCA Module 0 Capture/Compare Flag)
// PCA0CN0::CCF1 (PCA Module 1 Capture/Compare Flag)
// PCA0CN0::CCF2 (PCA Module 2 Capture/Compare Flag)
// PCA0CN0::CF (PCA Counter/Timer Overflow Flag)
// PCA0PWM::COVF (Cycle Overflow Flag)
//
//-----------------------------------------------------------------------------

SI_INTERRUPT (PCA0_ISR, PCA0_IRQn)
{
  if(PCA0CN0_CCF0){
      PCA0CPL0 = pwm_channels[0].u8[1];
      PCA0CPH0 = pwm_channels[0].u8[0];
      PCA0CN0_CCF0 = 0;
  }else if(PCA0CN0_CCF1){
      PCA0CPL1 = pwm_channels[1].u8[1];
      PCA0CPH1 = pwm_channels[1].u8[0];
      PCA0CN0_CCF1 = 0;
  }
  PCA0CN0_CF = 0;
}


//-----------------------------------------------------------------------------
// UART1_ISR
//-----------------------------------------------------------------------------
//
// UART1 ISR Content goes here. Remember to clear flag bits:
// SCON1::RI (Receive Interrupt Flag)
// SCON1::TI (Transmit Interrupt Flag)
// UART1FCN1::RFRQ (Receive FIFO Request)
// UART1FCN1::TFRQ (Transmit FIFO Request)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (UART1_ISR, UART1_IRQn)
{
  if(SCON1_RI){
    uint8_t tmp = SBUF1;
    SCON1_RI = 0;
    sbus_packet[sbus_cntr]=tmp;
    sbus_packet_received = false;
    if(sbus_cntr<24) sbus_cntr++;
  }
}

//-----------------------------------------------------------------------------
// TIMER2_ISR
//-----------------------------------------------------------------------------
//
// TIMER2 ISR Content goes here. Remember to clear flag bits:
// TMR2CN0::TF2H (Timer # High Byte Overflow Flag)
// TMR2CN0::TF2L (Timer # Low Byte Overflow Flag)
//
//-----------------------------------------------------------------------------
SI_INTERRUPT (TIMER2_ISR, TIMER2_IRQn)
{
  if(sbus_cntr==24) sbus_packet_received = true;
  sbus_cntr = 0; // reset counter as UART1 timeout occurred
  TMR2CN0_TF2H = 0;
}

//-----------------------------------------------------------------------------
// TIMER3_ISR
//-----------------------------------------------------------------------------
//
// TIMER3 ISR Content goes here. Remember to clear flag bits:
// TMR3CN0::TF3H (Timer # High Byte Overflow Flag)
// TMR3CN0::TF3L (Timer # Low Byte Overflow Flag)
//
//-----------------------------------------------------------------------------
// Overflows every 16ms
SI_INTERRUPT (TIMER3_ISR, TIMER3_IRQn)
{
  TMR3CN0 &= ~(TMR3CN0_TF3H__BMASK);
  delay_powering_counter++;
  timeout_tick = true;

  led_pattern_counter++;
  if(led_pattern == 0){
      PIN_LED = 1; // OFF
      led_pattern_counter = 0;
  }else if(led_pattern == 1){
      PIN_LED = 0; // ON
      led_pattern_counter = 0;
  }else if(led_pattern == 2){
      if(led_pattern_counter < 5){
          PIN_LED = 0; // ON
      }else if(led_pattern_counter < 10){
          PIN_LED = 1; // OFF
      }else led_pattern_counter = 0;
  }else if(led_pattern == 3){
      if(led_pattern_counter < 80){
          PIN_LED = 0; // ON
      }else if(led_pattern_counter < 100){
          PIN_LED = 1; // OFF
      }else led_pattern_counter = 0;
  }

  // start new ADC conversion
  SFRPAGE = 0x00; // now we can screw SFR page
  if(!ADC0CN0_ADINT){
      ADC0CN0_ADBUSY = true;
  }
}


SI_INTERRUPT (PWM0_ISR, PWM_IRQn)
{
  PWMIF &= ~PWMIF_CTROVIF__BMASK;

  PWMCPUDL0 = pwm_channels[2].u8[1];
  PWMCPUDH0 = pwm_channels[2].u8[0];
  PWMCPUDL1 = pwm_channels[3].u8[1];
  PWMCPUDH1 = pwm_channels[3].u8[0];

}
