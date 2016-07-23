/*
 * PinIn.h
 *
 *  Created on: 06.03.2016
 *      Author: patrick
 */

#ifndef AVRP_PININ_H_
#define AVRP_PININ_H_

#include <avr/io.h>

namespace avrp {

template <uint8_t Pin> class PinIn_PortB {
public:
	static bool getState();
};

template <uint8_t Pin> class PinIn_PortC {
public:
	static bool getState();
};

template <uint8_t Pin> class PinIn_PortD {
public:
	static bool getState();
};

} /* namespace avrp */

#include "PinIn.cpp" // template

#endif /* AVRP_PININ_H_ */
