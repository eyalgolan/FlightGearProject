//
// Created by eyal on 16/12/19.
//

#include "ConditionParser.h"
#include "iostream"

using namespace std;

int ConditionParser::exec(vector<string> params) {

  return this->numParams;
}
ConditionParser::ConditionParser(double var, string op, double value) {
  if(op == ">"){
    if(var > value) {
      this->condition = true;
    }
    else{
      this->condition = false;
    }
  }
  else if(op == ">="){
    if(var >= value) {
      this->condition = true;
    }
    else{
      this->condition = false;
    }
  }
  else if(op == "<"){
    if(var < value) {
      this->condition = true;
    }
    else {
      this->condition = false;
    }
  }
  else if(op == "<="){
    if(var <= value) {
      this->condition = true;
    }
    else {
      this->condition = false;
    }
  }
  else if(op == "=="){
    if(var == value) {
      this->condition = true;
    }
    else{
      this->condition = false;
    }
  }
  else if(op == "!="){
    if(var != value) {
      this->condition = true;
    }
    else {
      this->condition = false;
    }
  }
  else{
    cout<<"didnt find condition"<<endl;
  }
}