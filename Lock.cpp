//
// Created by eyal on 24/12/19.
//

#include "Lock.h"
#include "mutex"

void Lock::lockIt() {
  this->lock.lock();
}
void Lock::unlockIt() {
  this->lock.unlock();
}