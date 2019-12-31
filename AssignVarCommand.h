//
// Created by eyal on 24/12/19.
//

#ifndef FLIGHTGEARPROJECT_ASSIGNVARCOMMAND_H
#define FLIGHTGEARPROJECT_ASSIGNVARCOMMAND_H

#import "Command.h"

class AssignVarCommand : public Command{
 private:
  int numParams = 4;
 public:
  int exec(vector<string> params) override;
};

#endif //FLIGHTGEARPROJECT_ASSIGNVARCOMMAND_H
