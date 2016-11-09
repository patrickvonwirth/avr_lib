/*
 * TWISlave.cpp
 *
 *  Created on: 29.10.2016
 *      Author: patrick
 */

#ifndef SRC_AVR_LIB_AVRP_TWISLAVE_CPP_ // template
#define SRC_AVR_LIB_AVRP_TWISLAVE_CPP_

#include "TWISlave.h"

#include <util/twi.h>

namespace avrp {

template<uint8_t rw_buffer_size, F_TWI_event onDataReceive, F_TWI_event onDataRequest>
volatile _TWI_State TWISlave<rw_buffer_size, onDataReceive, onDataRequest>::state = _twi_off;

template<uint8_t rw_buffer_size, F_TWI_event onDataReceive, F_TWI_event onDataRequest>
uint8_t TWISlave<rw_buffer_size, onDataReceive, onDataRequest>::next_transmit_byte = 0;

template<uint8_t rw_buffer_size, F_TWI_event onDataReceive, F_TWI_event onDataRequest>
uint8_t TWISlave<rw_buffer_size, onDataReceive, onDataRequest>::data[rw_buffer_size] = {};

template<uint8_t rw_buffer_size, F_TWI_event onDataReceive, F_TWI_event onDataRequest>
uint8_t TWISlave<rw_buffer_size, onDataReceive, onDataRequest>::data_size = 0;

template<uint8_t rw_buffer_size, F_TWI_event onDataReceive, F_TWI_event onDataRequest>
void TWISlave<rw_buffer_size, onDataReceive, onDataRequest>::start(const uint8_t address, const bool generalcall_enable) {
  TWAR = (address << 1) | generalcall_enable; // store slave address and general call enable flag before activating TWI
  state = _twi_ready;
  TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN) | (1 <<TWIE); // activate TWI listening to address matches
}

template<uint8_t rw_buffer_size, F_TWI_event onDataReceive, F_TWI_event onDataRequest>
void TWISlave<rw_buffer_size, onDataReceive, onDataRequest>::stop() {
  TWCR = 0b00000000;
  state = _twi_off;
}

template<uint8_t rw_buffer_size, F_TWI_event onDataReceive, F_TWI_event onDataRequest>
void TWISlave<rw_buffer_size, onDataReceive, onDataRequest>::onInterrupt() {
  uint8_t twi_status = (TWSR & 0b11111000);
  switch (state) {
    case _twi_ready:
      onTWIready(twi_status);
      break;
    case _twi_receive:
      onTWIreceive(twi_status);
      break;
    case _twi_transmit:
      onTWItransmit(twi_status);
      break;
    default: // _twi_off
      return; // do not activate TWI
  }
}

template<uint8_t rw_buffer_size, F_TWI_event onDataReceive, F_TWI_event onDataRequest>
void TWISlave<rw_buffer_size, onDataReceive, onDataRequest>::onTWIready(const uint8_t TWI_state) {
  switch (TWI_state) {
    case TW_SR_SLA_ACK: // initialize new data receive
    case TW_SR_GCALL_ACK:
      state = _twi_receive;
      data_size = 0; // reset data for new incoming data
      TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN) | (1 <<TWIE); // reactivate TWI answering ACK, assume at least one byte buffer
      break;
    case TW_ST_SLA_ACK: // initialize new plain data transmit
      data_size = 0; // to show no data receive before transmit
      onDataRequest();
      next_transmit_byte = 0;
      state = _twi_transmit;
      //TODO: implement data transmit start
      break;
    default: // ERROR
      // remain in state ready
      TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN) | (1 <<TWIE); // reactivate TWI listening to address matches
  }
}

template<uint8_t rw_buffer_size, F_TWI_event onDataReceive, F_TWI_event onDataRequest>
void TWISlave<rw_buffer_size, onDataReceive, onDataRequest>::onTWIreceive(const uint8_t TWI_state) {
  switch (TWI_state) {
    case TW_SR_DATA_ACK: // collect and buffer incoming data
    case TW_SR_GCALL_DATA_ACK:
      data[data_size] = TWDR; // collect data
      data_size += 1;
      if (data_size == rw_buffer_size) { // buffer full
        TWCR = (1<<TWINT) | (0<<TWEA) | (1<<TWEN) | (1 <<TWIE); // reactivate TWI answering NACK
      } else { // buffer bytes left
        TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN) | (1 <<TWIE); // reactivate TWI answering ACK
      }
      break;
    case TW_SR_DATA_NACK: // data received, but ignored, since the buffer is full
    case TW_SR_GCALL_DATA_NACK:
      TWCR = (1<<TWINT) | (0<<TWEA) | (1<<TWEN) | (1 <<TWIE); // reactivate TWI answering NACK
      break;
    case TW_SR_STOP: // finished, process data
      onDataReceive();
      state = _twi_ready;
      TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN) | (1 <<TWIE); // activate TWI listening to address matches
      break;
    case TW_ST_SLA_ACK: // start data transmission after received data
      onDataRequest();
      next_transmit_byte = 0;
      state = _twi_transmit;
      //TODO: implement data transmit start
      break;
    default: // ERROR
      state = _twi_ready; // return to ready
      TWCR = (1<<TWINT) | (1<<TWEA) | (1<<TWEN) | (1 <<TWIE); // activate TWI listening to address matches
      break;
  }
}

template<uint8_t rw_buffer_size, F_TWI_event onDataReceive, F_TWI_event onDataRequest>
void TWISlave<rw_buffer_size, onDataReceive, onDataRequest>::onTWItransmit(const uint8_t TWI_state) {
  // TODO: implement
}

} /* namespace avrp */

#endif /* SRC_AVR_LIB_AVRP_TWISLAVE_CPP_ */
