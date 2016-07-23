/*
 * PinOut.cpp
 *
 *  Created on: 18.02.2016
 *      Author: patrick
 */

#ifndef AVRP_PINOUT_CPP_ // template
#define AVRP_PINOUT_CPP_

#include "PinOut.h"

namespace avrp {

template <uint8_t Pin> void PinOut_PortB<Pin>::setActive(bool a_active) {
	if (a_active) {
		PORTB |= (1 << Pin);
	} else {
		PORTB &= ~(1 << Pin);
	}
}

template <uint8_t Pin> void PinOut_PortB<Pin>::pulse() {
	setActive(true);
	setActive(false);
}

template <uint8_t Pin> void PinOut_PortC<Pin>::setActive(bool a_active) {
	if (a_active) {
		PORTC |= (1 << Pin);
	} else {
		PORTC &= ~(1 << Pin);
	}
}

template <uint8_t Pin> void PinOut_PortC<Pin>::pulse() {
	setActive(true);
	setActive(false);
}

template <uint8_t Pin> void PinOut_PortD<Pin>::setActive(bool a_active) {
	if (a_active) {
		PORTD |= (1 << Pin);
	} else {
		PORTD &= ~(1 << Pin);
	}
}

template <uint8_t Pin> void PinOut_PortD<Pin>::pulse() {
	setActive(true);
	setActive(false);
}

} /* namespace avrp */

#endif /* AVRP_PINOUT_CPP_ */
