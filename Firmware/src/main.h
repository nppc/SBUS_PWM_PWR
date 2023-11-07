#include <SI_EFM8BB51_Register_Enums.h>                  // SFR declarations
#include <SI_EFM8BB51_Defs.h>
#include <stdint.h>

#ifndef MAIN_H_
#define MAIN_H_


// Structure for accessing 16bit number by 2 8 bit (back and forth)
// Usage:
// U16_U8 ptr;
// ptr.u8[0] = high;
// ptr.u8[1] = low;
// ptr.u16 = 16bit;
typedef union
   {
   unsigned short u16;
   unsigned char u8[2];
   } U16_U8;

extern void waitNms(uint16_t ms);
extern uint16_t convert_sbus_2_pwm(uint16_t val);
extern void goPowerDown(void);
extern bit isVoltageLow(void);

//SI_SBIT(PIN_PWM1, SFR_P1, 5); // TSSOP-20 PIN10
//SI_SBIT(PIN_PWM2, SFR_P0, 2); // TSSOP-20 PIN2
//SI_SBIT(PIN_PWM3, SFR_P0, 4); // TSSOP-20 PIN20
//SI_SBIT(PIN_PWM4, SFR_P1, 4); // TSSOP-20 PIN11
//SI_SBIT(PIN_SBUS, SFR_P1, 0); // TSSOP-20 PIN16
SI_SBIT(PIN_LED, SFR_P0, 5);  // TSSOP-20 PIN19
SI_SBIT(PIN_MOSFET, SFR_P0, 3); // TSSOP-20 PIN1
SI_SBIT(PIN_BUTA, SFR_P1, 2); // TSSOP-20 PIN13
SI_SBIT(PIN_BUTB, SFR_P1, 1); // TSSOP-20 PIN15
SI_SBIT(PIN_BUT_SENS, SFR_P1, 3); // TSSOP-20 PIN12
// CLU1A TSSOP-20 PIN 16


extern U16_U8 pwm_channels[];
extern bit PWM_started;
extern uint8_t delay_powering_counter;
extern uint8_t led_pattern, led_pattern_counter;
extern uint16_t timeout_counter;
extern bit timeout_tick;

#endif /* MAIN_H_ */
