/*
 * Randuint8.cpp
 *
 *  Created on: 23.07.2016
 *      Author: patrick
 */

#include "Randuint8.h"

#include <avr/eeprom.h>
#include <stdlib.h>

namespace avrp {

uint16_t EEMEM _randuint8_eeprom_seed = 0xAA55; // arbitrary value as first seed

void sranduint8_eeprom() {
  uint16_t seed = eeprom_read_word(&_randuint8_eeprom_seed);
  srand(seed);
  seed ^= rand();
  eeprom_write_word(&_randuint8_eeprom_seed, seed);
}

uint8_t randuint8() {
  return uint8_t(rand() >> 8); // use high byte of random number
}

} /* namespace avrp */
