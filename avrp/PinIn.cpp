/*
 * PinIn.cpp
 *
 *  Created on: 06.03.2016
 *      Author: patrick
 */

#ifndef AVRP_PININ_CPP_ // template
#define AVRP_PININ_CPP_

#include "PinIn.h"

namespace avrp {

template <uint8_t Pin> bool PinIn_PortB<Pin>::getState() {
  return ((PINB & (1 << Pin)) > 0);
}

template <uint8_t Pin> bool PinIn_PortC<Pin>::getState() {
  return ((PINC & (1 << Pin)) > 0);
}

template <uint8_t Pin> bool PinIn_PortD<Pin>::getState() {
  return ((PIND & (1 << Pin)) > 0);
}

} /* namespace avrp */

#endif /* AVRP_PININ_CPP_ */
