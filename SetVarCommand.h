//
// Created by eyal on 24/12/19.
//

#ifndef FLIGHTGEARPROJECT_SETVARCOMMAND_H
#define FLIGHTGEARPROJECT_SETVARCOMMAND_H

#import "Command.h"
class SetVarCommand : public Command{
 private:
  int numParams = 2;
 public:
  int exec(vector<string> params) override;
};

#endif //FLIGHTGEARPROJECT_SETVARCOMMAND_H