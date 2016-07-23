/*
 * PortIn.h
 *
 *  Created on: 23.07.2016
 *      Author: patrick
 */

#ifndef AVRP_PORTIN_H_
#define AVRP_PORTIN_H_

#include <avr/io.h>

namespace avrp {

template <uint8_t Mask> class PortIn_PortB {
public:
  static uint8_t getState();
};

template <uint8_t Mask> class PortIn_PortC {
public:
  static uint8_t getState();
};

template <uint8_t Mask> class PortIn_PortD {
public:
  static uint8_t getState();
};

} /* namespace avrp */

#include "PortIn.cpp" // template

#endif /* AVRP_PORTIN_H_ */
