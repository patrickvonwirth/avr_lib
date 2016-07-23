/*
 * PortIn.cpp
 *
 *  Created on: 23.07.2016
 *      Author: patrick
 */

#ifndef AVRP_PORTIN_CPP_ // template
#define AVRP_PORTIN_CPP_

#include "PortIn.h"

namespace avrp {

template <uint8_t Mask> uint8_t PortIn_PortB<Mask>::getState() {
  return (PINB & Mask);
}

template <uint8_t Mask> uint8_t PortIn_PortC<Mask>::getState() {
  return (PINC & Mask);
}

template <uint8_t Mask> uint8_t PortIn_PortD<Mask>::getState() {
  return (PIND & Mask);
}

} /* namespace avrp */

#endif /* AVRP_PORTIN_CPP_ */
