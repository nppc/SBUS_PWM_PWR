#ifndef SRC_SBUS_H_
#define SRC_SBUS_H_

#include <stdint.h>

extern uint8_t sbus_cntr;
extern uint8_t sbus_packet[];
extern uint16_t sbus_ch[];
extern bit sbus_packet_received;

extern bit sbus_parse(void);

#define SBUS_HEADER           0x0f
#define SBUS_LOST_FRAME_MASK  0x04
#define SBUS_FAILSAFE_MASK    0x08

#endif /* SRC_SBUS_H_ */
