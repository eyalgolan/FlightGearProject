//
// Created by yair on 30/12/2019.
//
#include <iostream>
#include "Expression.h"
#include "map"

using namespace std;
#ifndef FLIGHTGEARPROJECT_EXPRESSIONHANDLER_H
#define FLIGHTGEARPROJECT_EXPRESSIONHANDLER_H



class ex1 {

};
class Value : public virtual Expression{
 private:  double  v;
 public: Value(double val);
  double calculate();
};
class BinaryOperator : public virtual Expression{
 protected:   Expression* left;
 protected:   Expression* right;
 public: BinaryOperator(Expression* l ,Expression* r);
};
class UnaryOperator : public  virtual  Expression{
 protected:Expression* one;
 public:  UnaryOperator(Expression* k);
};
class UPlus: public UnaryOperator{
//public: UnaryOperator u;
 public: UPlus(Expression *k);

  double calculate();

};
class UMinus: public UnaryOperator{
 public:   UMinus(Expression *k);
  double calculate();

};
class Plus: public BinaryOperator{
//protected:Expression* right;
//protected:Expression* left;
 public: Plus(Expression *l, Expression *r);
  double calculate();

};

class Minus: public BinaryOperator{
//protected:Expression* right;
//protected:Expression* left;
 public: Minus(Expression* l,Expression* r);
  double calculate();

};
class Mul: public BinaryOperator{
//protected:Expression* right;
//protected:Expression* left;
 public:   Mul(Expression* l,Expression* r);
  double calculate();

};
class Div: public BinaryOperator{
//protected:Expression* right;
//protected:Expression* left;
 public:   Div(Expression* l,Expression* r);
  double calculate();

};
class Variable:public  virtual Expression{
 private: string name;
 private: double va;
 public: Variable(string na, double v);

 public: Variable& operator++();
 public: Variable& operator--();
 public: Variable& operator+=(double num);
 public: Variable& operator-=(double num);
 public: Variable& operator++(int);
 public: Variable& operator--(int);

  double calculate();
};
class Interpreter{
 public: string st;
 public: map<string,double >mymap;
 public: Interpreter();
 public:Expression* interpret(string s);

 public: void setVariables(string str);
 public: bool isoperator(char c);
 public: bool isoperator(string c);

 public:bool isoperant(char c);
 public:bool isoperant(string c);

 public:int compare(char a,char b);

 public:
  double infixtopostfix(string infix);
};


#endif //FLIGHTGEARPROJECT_EXPRESSIONHANDLER_H