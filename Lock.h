//
// Created by eyal on 24/12/19.
//

#ifndef FLIGHTGEARPROJECT_LOCK_H
#define FLIGHTGEARPROJECT_LOCK_H

#import "mutex"

using namespace std;

class Lock {
 public:
  static Lock &getInstance() {
    static Lock instance;
    return instance;
  }
  Lock(Lock const&) = delete;
  void operator=(Lock const&) = delete;
  void lockIt();
  void unlockIt();
 private:
  Lock(){}
  mutex lock;
};

#endif //FLIGHTGEARPROJECT_LOCK_H
