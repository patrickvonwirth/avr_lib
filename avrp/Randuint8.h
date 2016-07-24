/*
 * Randuint8.h
 *
 *  Created on: 23.07.2016
 *      Author: patrick
 */

#ifndef SRC_AVR_LIB_AVRP_RANDUINT8_H_
#define SRC_AVR_LIB_AVRP_RANDUINT8_H_

#include <avr/io.h>

namespace avrp {

// initializes the rand-function from an eepmem value and stores a random value as new seed in the eeprom
void sranduint8_eeprom();

uint8_t randuint8();

} /* namespace avrp */

#endif /* SRC_AVR_LIB_AVRP_RANDUINT8_H_ */
