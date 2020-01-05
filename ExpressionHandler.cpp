#include <iostream>
#include "Expression.h"
#include "ExpressionHandler.h"
#include "stack"
#include "queue"
#include "string"
#include "exception"

using namespace std;
// constructor
Value::Value(double val) {
  this->v = val;
}
// constructor

double Value::calculate() {
  return v;
}
// constructor

UnaryOperator::UnaryOperator(Expression *k) : one(k) {
}
BinaryOperator::BinaryOperator(Expression *l, Expression *r)
    : left(l), right(r) {}
UPlus::UPlus(Expression *k) : UnaryOperator(k) {
}
double UPlus::calculate() {
  return this->one->calculate();
}
UMinus::UMinus(Expression *k) : UnaryOperator(k) {
}
double UMinus::calculate() {
  return (this->one->calculate() * (-1));
}
// constructor

Plus::Plus(Expression *l, Expression *r) : BinaryOperator(l, r) {

}
double Plus::calculate() {
  return (this->left)->calculate() + (this->right)->calculate();
}
Minus::Minus(Expression *l, Expression *r) : BinaryOperator(l, r) {

}
// constructor

double Minus::calculate() {
  return (this->left)->calculate() - (this->right)->calculate();
}
Mul::Mul(Expression *l, Expression *r) : BinaryOperator(l, r) {

}
double Mul::calculate() {
  return (this->left)->calculate() * (this->right)->calculate();
}
Div::Div(Expression *l, Expression *r) : BinaryOperator(l, r) {

}
double Div::calculate() {
  if (this->right->calculate() == 0) {
    throw ("division by zero");
  }
  return (this->left)->calculate() / (this->right)->calculate();
}
Variable::Variable(string na, double v) : name(na), va(v) {
}// constructor
Variable &Variable::operator++() {
  this->va = this->va + 1;
  return *this;
}
// constructor
Variable &Variable::operator--() {
  this->va = this->va - 1;
  return *this;
}
// constructor
Variable &Variable::operator+=(double num) {
  this->va = va + num;
  return *this;
}
Variable &Variable::operator-=(double num) {
  this->va = va - num;
  return *this;
}
// constructor
Variable &Variable::operator++(int) {
  this->va = va + 1;
  return *this;
}
// constructor
Variable &Variable::operator--(int) {
  this->va = va - 1;
  return *this;
}
double Variable::calculate() {
  return this->va;
}

Interpreter::Interpreter() {}
// bool is operator
bool Interpreter::isoperator(char c) {
  if (c == '+' || c == '-' || c == '*' || c == '/') {

    return true;
  } else {
    return false;
  }
}
// bool is operator
bool Interpreter::isoperator(string c) {
  if (c == "+" || c == "-" || c == "*" || c == "/") {

    return true;
  } else {
    return false;
  }
}

// cheak if operant
bool Interpreter::isoperant(char c) {
  if (!isoperator(c) && c != '(' && c != ')' && c != '\0') {

    return true;
  }
  return false;
}
// cheak if operant
bool Interpreter::isoperant(string c) {
  if (!isoperator(c) && c != "(" && c != ")" && c != "\0") {

    return true;
  }
  return false;
}
// compare funk
int Interpreter::compare(char a, char b) {
  if ((a == '*' || a == '/') && (b == '+' || b == '-')) { return -1; }

  else if ((a == '+' || a == '-') && (b == '*' || b == '/')) { return 1; }

  return 0;
}
/**
 * the funk get indix string
 * convert it to postfix and the evaluate it with
 * shunting-yard algorithm and evaluate the number
 * @param infix
 * @return evaluate of the postfix
 */
double Interpreter::infixtopostfix(string infix) {
  stack<char> os;
  stack<double> ev;
  queue<string> qu;
  string post = "";
  int i = 0;
  int f = 0;
  // reading the string to buffers
  while (infix[i] != '\0') {
    if (isoperant(infix[i])) {
      post += infix[i];
      string g = "";
      g += infix[i];
      while (isoperant(infix[i + f + 1])) {

        g += infix[i + f + 1];
        f++;
      }
      qu.push(g);

    } // cheaking the operator
    else if (isoperator(infix[i])) {
      //chaining the chars of the parameters
      while (!os.empty() && os.top() != '('
          && compare(os.top(), infix[i]) <= 0) {
        post += os.top();
        string g = "";
        g = os.top();
        qu.push(g);
        os.pop();
      }
      // cheak the '-' char
      if ((infix[i] == '-')
          && ((isoperator(infix[i - 1])) || (infix[i - 1] == '(')
              || (&infix[i] == &infix[0]))) {
        os.push('$');
      }// cheak the '+' char
      else if ((infix[i] == '+')
          && ((isoperator(infix[i - 1])) || (infix[i - 1] == '(')
              || (&infix[i] == &infix[0]))) {
        os.push('#');
      } else {
        os.push(infix[i]);

      }// error
      if (isoperator(infix[i + 1])) {
        throw ("illegal math expression");
      }
      // scope cheak
    } else if (infix[i] == '(') { os.push(infix[i]); }
    else if (infix[i] == ')') {
      while (!os.empty()) {
        if (os.top() == '(') {
          os.pop();
          break;
        }
        post += os.top();
        string g = "";
        g = os.top();
        qu.push(g);
        os.pop();
      }
    }
    i = f + i + 1;
    f = 0;
  }
  // chaining the chars of the operators.
  while (!os.empty()) {

    post += os.top();
    string g = "";
    g = os.top();
    qu.push(g);

    os.pop();

  }
  int j = 0;;
  int size = qu.size();
  while (j < size) {
    string fir = "";
    fir = qu.front();

    //  if (!(isoperator(post[j]))&&(isoperant(post[j]))){
    if (!(isoperator(qu.front())) && (isoperant(qu.front()))
        && qu.front() != "$"
        && qu.front() != "#") {
      // ev.push(post[j]-'0');
      string k = "";
      k = qu.front();
      if (isdigit(k[0]) != 0) {
        ev.push(stod(k, NULL));
        qu.pop();
      }
        // delete the scops
      else {
        int start_pos = 0;
        while ((start_pos = k.find(" ", start_pos)) != string::npos) {
          k.replace(start_pos, 1, "");
          start_pos += 0;
        }
        if (this->mymap.find(k) == mymap.end()) {
          throw ("iligal math expresssion");
        }
        ev.push(this->mymap[k]);
        qu.pop();
      }

    }
      // spicial charactar $ using the algorithm
    else if (qu.front() == "$") {

      double val1 = ev.top();
      ev.pop();
      ev.push((-1) * val1);
      qu.pop();
    }
      // spicial charactar # using the algorithm

    else if (qu.front() == "#") {
      double val1 = ev.top();
      ev.pop();
      ev.push((1) * val1);
      qu.pop();
    }
      // the shunting-yard algorithm

    else {
      double val1 = ev.top();
      ev.pop();
      double val2 = ev.top();
      ev.pop();
      switch (qu.front()[0]) {
        case '+': ev.push(val2 + val1);

          //   qu.push(to_string(val2+val1));
          qu.pop();

          break;
        case '-': ev.push(val2 - val1);
          qu.pop();
          break;
        case '*': ev.push(val2 * val1);
          qu.pop();

          break;
        case '/': ev.push(val2 / val1);
          if (val1 == 0) {
            throw ("division by zero");
          }
          qu.pop();
          break;
      }

    }
    j++;
  }
  double ch = ev.top();
  return ch;
  // return post;
}
/**
 *
 * @param s get the string that we want to evaluate
 * @return  double after infix to post fix and the evaluate
 */
Expression *Interpreter::interpret(string s) {
  Expression *v = new Value(infixtopostfix(s));
  return v;
}
// set the variabkes
void Interpreter::setVariables(string str) {
  int i = 0;

  while (i < (int) str.length()) {
    string damya;
    string damyb;
// cheaking the variables
    if (isalpha(str[i]) != 0) {
      while (str[i] != '=') {

        damya += str[i];
        i++;
      }
      if (str[i] == '=') {
        i++;
//                if ((isdigit(str[i])==0)&&(str[i]!='-')){
//                    throw ("illegal variable assignment!");

      }
    }

// chainings the chars of the variable
    while (isdigit(str[i]) != 0
        || ((str[i] == '-') && isdigit(str[i + 1]) != 0)) {
      damyb += str[i];
      i++;

      if ((isdigit(str[i - 1]) != 0) && (isdigit(str[i + 1]) != 0)
          && ((str[i]) == '.')) {
        damyb += str[i];
        i++;
      }
    }

    this->mymap[damya] = stod(damyb);
    if (str[i] == ';') {
      i++;
    }

  }
}