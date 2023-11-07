#include "main.h"
#include "adc.h"

// (36/289) - VDD_DIV divider from datasheet
// ADC_V_CONST = VREF / 4095 / (36/289)
// ADC_V_CONST = 1200 / 4095 / (36/289)
#define ADC_V_CONST 2.352462352

// Calculate 12 bit ADC value for given Voltage (1.2V VREF)
// ADC = Voltage * (36/289) * 4095 / 1.2


// returns voltage in mV
// if 0 then there is no new voltage reading ready
uint16_t readVoltage(void){
  uint16_t lastVoltage = 0;
  // new conversion started in TIMER3 interrupt every 16ms
  if(ADC0CN0_ADINT){
      uint16_t adcval = ADC0;
      ADC0CN0_ADINT = false;
      // convert ADC to Voltage (mv)
      // Voltage = ADC * const
      lastVoltage = (uint16_t)((float)adcval * ADC_V_CONST);
  }
  return lastVoltage;
}
