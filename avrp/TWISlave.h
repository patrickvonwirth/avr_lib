/*
 * TWISlave.h
 *
 *  Created on: 29.10.2016
 *      Author: patrick
 */

#ifndef SRC_AVR_LIB_AVRP_TWISLAVE_H_
#define SRC_AVR_LIB_AVRP_TWISLAVE_H_

#include <avr/io.h>

namespace avrp {

enum _TWI_State {
  _twi_off,
  _twi_ready,
  _twi_receive,
  _twi_transmit,
  _twi_STATE_COUNT // this has to be the last, it gives the number of states
};

typedef void (*F_TWI_event)();

template<uint8_t rw_buffer_size, F_TWI_event onDataReceive, F_TWI_event onDataRequest> class TWISlave {
  // assume rw_buffer_size > 0
private:
  static volatile _TWI_State state;
  static uint8_t next_transmit_byte;
  static void onTWIready(const uint8_t TWI_state);
  static void onTWIreceive(const uint8_t TWI_state);
  static void onTWItransmit(const uint8_t TWI_state);
public:
  static uint8_t data[rw_buffer_size];
  static uint8_t data_size;
  static void start(const uint8_t address, const bool generalcall_enable);
  static void stop();
  static void onInterrupt();
};

} /* namespace avrp */

#include "TWISlave.cpp" // template

#endif /* SRC_AVR_LIB_AVRP_TWISLAVE_H_ */
