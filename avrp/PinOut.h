/*
 * PinOut.h
 *
 *  Created on: 18.02.2016
 *      Author: patrick
 */

#ifndef AVRP_PINOUT_H_
#define AVRP_PINOUT_H_

#include <avr/io.h>

namespace avrp {

template <uint8_t Pin> class PinOut_PortB {
public:
	static void setActive(bool a_active);
	static void pulse();
};

template <uint8_t Pin> class PinOut_PortC {
public:
	static void setActive(bool a_active);
	static void pulse();
};

template <uint8_t Pin> class PinOut_PortD {
public:
	static void setActive(bool a_active);
	static void pulse();
};

} /* namespace avrp */

#include "PinOut.cpp" // template

#endif /* AVRP_PINOUT_H_ */
