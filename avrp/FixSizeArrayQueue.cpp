/*
 * FixSizeArrayQueue.cpp
 *
 *  Created on: 24.07.2016
 *      Author: patrick
 */

#ifndef AVRP_FIXSIZEARRAYQUEUE_CPP_ // template
#define AVRP_FIXSIZEARRAYQUEUE_CPP_

#include "FixSizeArrayQueue.h"

namespace avrp {

template<uint8_t sizeBits, typename Type> volatile Type FixSizeArrayQueue<sizeBits, Type>::elements[_ONES >> (8-sizeBits)] = {};
template<uint8_t sizeBits, typename Type> volatile uint8_t FixSizeArrayQueue<sizeBits,Type>::readPos = 0;
template<uint8_t sizeBits, typename Type> volatile uint8_t FixSizeArrayQueue<sizeBits,Type>::writePos = 0;
template<uint8_t sizeBits, typename Type> volatile bool FixSizeArrayQueue<sizeBits,Type>::empty = true;

template<uint8_t sizeBits, typename Type> bool FixSizeArrayQueue<sizeBits,Type>::push(const Type a_Element) {
  if ((readPos == writePos) && !empty) {
    return false;
  } else {
    elements[writePos] = a_Element;
    writePos = (writePos + 1) & (_ONES >> (8-sizeBits)); // modulo real size
    empty = false;
    return true;
  }
}

template<uint8_t sizeBits, typename Type> bool FixSizeArrayQueue<sizeBits,Type>::popInto(Type *a_Dest) {
  if (empty) {
    return false;
  } else {
    *a_Dest = elements[readPos];
    readPos = (readPos + 1) & (_ONES >> (8-sizeBits)); // modulo real size
    empty = (readPos == writePos);
    return true;
  }
}

} /* namespace avrp */

#endif /* AVRP_FIXSIZEARRAYQUEUE_CPP_ */
