#include "sbus.h"
#include "main.h"

volatile uint8_t sbus_packet[25];
volatile uint8_t sbus_cntr = 0;
volatile uint16_t sbus_ch[4];
volatile bit sbus_packet_received = false;

// Returns validity of packet (no failsafe or similar)
bit sbus_parse(void){
  bit lost_frame_bit, failsafe_bit;
  bit returnval = false;
  if(sbus_packet[0]== SBUS_HEADER){
    sbus_ch[0] = (int16_t)(sbus_packet[1] |
                                ((sbus_packet[2] << 8) & 0x07FF));
    sbus_ch[1]  = (int16_t)((sbus_packet[2] >> 3) |
                                ((sbus_packet[3] << 5) & 0x07FF));
    sbus_ch[2]  = (int16_t)((sbus_packet[3] >> 6) |
                                (sbus_packet[4] << 2) |
                                ((sbus_packet[5] << 10) & 0x07FF));
    sbus_ch[3]  = (int16_t)((sbus_packet[5] >> 1) |
                                ((sbus_packet[6] << 7) & 0x07FF));
    lost_frame_bit = sbus_packet[23] & SBUS_LOST_FRAME_MASK;
    failsafe_bit = sbus_packet[23] & SBUS_FAILSAFE_MASK;

    if(!lost_frame_bit && !failsafe_bit) returnval = true;
  }
  return returnval;
}
