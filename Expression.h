//
// Created by yair on 30/12/2019.
//

#ifndef FLIGHTGEARPROJECT_EXPRESSION_H
#define FLIGHTGEARPROJECT_EXPRESSION_H

using namespace std;
/**
 * Expression Interface
 */
class Expression {

public:
    virtual double calculate() = 0;
    virtual ~Expression() {}
};

#endif //FLIGHTGEARPROJECT_EXPRESSION_H
