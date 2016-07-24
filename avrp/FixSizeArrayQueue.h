/*
 * FixSizeArrayQueue.h
 *
 *  Created on: 24.07.2016
 *      Author: patrick
 */

#ifndef AVRP_FIXSIZEARRAYQUEUE_H_
#define AVRP_FIXSIZEARRAYQUEUE_H_

#include <avr/io.h>

#define _ONES 0b11111111

namespace avrp {

// sizeBits in [1,8] is the number of bits used as the queue size
template <uint8_t sizeBits, typename Type> class FixSizeArrayQueue {
private:
  static volatile Type elements[_ONES >> (8-sizeBits)];
  static volatile uint8_t readPos;
  static volatile uint8_t writePos;
  static volatile bool empty;
public:
  static bool push(const Type a_Element); // return false, if the queue is full and the element has not been pushed
  static bool popInto(Type *a_Dest); // return true, if an element has been written to a_Dest
};

} /* namespace avrp */

#include "FixSizeArrayQueue.cpp" // template

#endif /* AVRP_FIXSIZEARRAYQUEUE_H_ */
