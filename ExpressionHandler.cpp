#include <iostream>
#include "Expression.h"
#include "ExpressionHandler.h"
#include "stack"
#include "queue"
#include "string"
#include "exception"

using namespace std;

Value::Value(double val) {
  this->v=val;
}
double Value::calculate() {
  return v;
}
UnaryOperator::UnaryOperator(Expression* k):one(k) {
}
BinaryOperator::BinaryOperator(Expression *l, Expression *r):left(l),right(r) {}
UPlus::UPlus(Expression *k) : UnaryOperator(k) {
}
double UPlus::calculate() {
  return this->one->calculate();
}
UMinus::UMinus(Expression *k) : UnaryOperator(k) {
}
double UMinus::calculate() {
  return (this->one->calculate()*(-1));
}
Plus::Plus(Expression *l, Expression *r) : BinaryOperator(l, r) {

}
double Plus::calculate() {
  return  (this->left)->calculate()+(this->right)->calculate();
}
Minus::Minus(Expression *l, Expression *r) :BinaryOperator(l,r) {

}
double Minus::calculate() {
  return  (this->left)->calculate()-(this->right)->calculate();
}
Mul::Mul(Expression *l, Expression *r):BinaryOperator(l,r) {

}
double Mul::calculate() {
  return  (this->left)->calculate()*(this->right)->calculate();
}
Div::Div(Expression *l, Expression *r):BinaryOperator(l,r) {

}
double Div::calculate() {
  if (this->right->calculate()==0){
    throw("division by zero");
  }
  return  (this->left)->calculate()/(this->right)->calculate();
}
Variable::Variable(string na, double v): name(na),va(v){
  // this->name=na;
  //  this->va=v;
}
Variable& Variable::operator++() {
  this->va=this->va+1;
  return *this;
}
Variable& Variable::operator--() {
  this->va=this->va-1;
  return *this;
}

Variable& Variable::operator+=(double num) {
  this->va=va+num;
  return *this;
}
Variable& Variable::operator-=(double num) {
  this->va=va-num;
  return *this;
}
Variable& Variable::operator++(int) {
  this->va=va+1;
  return *this;
}
Variable& Variable::operator--(int) {
  this->va=va-1;
  return *this;
}
double Variable::calculate() {
  return this->va;
}

Interpreter::Interpreter(){}

bool Interpreter::isoperator(char c) {
  if (c == '+'|| c == '-' || c == '*' || c == '/') {

    return true;
  }
  else {
    return false;
  }
}
bool Interpreter::isoperator(string c) {
  if (c == "+"|| c == "-" || c == "*" || c == "/") {

    return true;
  }
  else {
    return false;
  }
}


bool Interpreter::isoperant(char c) {
  if (!isoperator(c) && c != '(' && c != ')' &&c !='\0') {

    return true;
  }
  return false;
}
bool Interpreter::isoperant(string c) {
  if (!isoperator(c) && c != "(" && c != ")" && c !="\0") {

    return true;
  }
  return false;
}
int Interpreter::compare(char a, char b) {
  if ((a == '*' || a == '/') && (b == '+' || b == '-')) { return -1; }

  else if ((a == '+' || a == '-') && (b == '*' || b == '/')) { return 1; }

  return 0;
}
double Interpreter::infixtopostfix(string infix) {
  stack<char> os;
  stack <double > ev;
  queue <string> qu;
  string post = "";
  int i = 0;
  int f=0;

  while (infix[i] != '\0') {
    if (isoperant(infix[i])) {
      post += infix[i];
      string g = "";
      g += infix[i];
      while (isoperant(infix[i+f+1])) {

        g += infix[i+f+1];
        f++;
      }
      qu.push(g);

    }
    else if (isoperator(infix[i]))
    {
      while (!os.empty() && os.top() != '(' && compare(os.top(), infix[i]) <= 0)
      {
        post += os.top();
        string g = "";
        g=os.top();
        qu.push(g);
        os.pop();
      }
      if((infix[i]=='-')&&((isoperator(infix[i-1]))||(infix[i-1]=='(')||(&infix[i]==&infix[0]))){
        os.push('$');
      }
      else if((infix[i]=='+')&&((isoperator(infix[i-1]))||(infix[i-1]=='(')||(&infix[i]==&infix[0]))){
        os.push('#');
      }
      else {
        os.push(infix[i]);

      }
      if(isoperator(infix[i+1])){
        throw("illegal math expression");
      }
    } else if (infix[i] == '(')
    { os.push(infix[i]); }
    else if (infix[i] == ')')
    {
      while (!os.empty())
      {
        if (os.top() == '(')
        {
          os.pop();
          break;
        }
        post += os.top();
        string g = "";
        g=os.top();
        qu.push(g);
        os.pop();
      }
    }
    i = f+i+1;
    f=0;
  }
  while (!os.empty()) {

    post += os.top();
    string g = "";
    g=os.top();
    qu.push(g);

    os.pop();

  }
  int j=0;;
  int size=qu.size();
  while(j<size)
  {
    string fir ="";
    fir = qu.front();

    //  if (!(isoperator(post[j]))&&(isoperant(post[j]))){
    if (!(isoperator(qu.front()))&&(isoperant(qu.front()))&& qu.front()!="$"
        && qu.front()!="#"){
      // ev.push(post[j]-'0');
      string k="";
      k=qu.front();
      if(isdigit(k[0])!=0) {
        ev.push(stod(k, NULL));
        qu.pop();
      }
      else {
        int start_pos = 0;
        while ((start_pos = k.find(" ", start_pos)) != string::npos)
        {
          k.replace(start_pos, 1, "");
          start_pos += 0; // Handles case where 'to' is a substring of 'from'
        }
        if(this->mymap.find(k)==mymap.end()){
          throw("iligal math expresssion");
        }
        ev.push(this->mymap[k]);
        qu.pop();
      }

    }
    else if (qu.front()=="$"){

      double val1=ev.top();
      ev.pop();
      ev.push((-1)*val1);
      qu.pop();
    }
    else if (qu.front()=="#"){
      double val1=ev.top();
      ev.pop();
      ev.push((1)*val1);
      qu.pop();
    }
    else {
      double val1=ev.top();
      ev.pop();
      double val2=ev.top();
      ev.pop();
      switch (qu.front()[0])
      {
        case '+': ev.push(val2+val1);

          //   qu.push(to_string(val2+val1));
          qu.pop();

          break;
        case '-': ev.push(val2-val1);
          qu.pop();
          break;
        case '*': ev.push(val2*val1);
          qu.pop();

          break;
        case '/': ev.push(val2/val1);
          if(val1==0){
            throw("division by zero");
          }
          qu.pop();
          break;
      }



    }
    j++;
  }
  double ch=ev.top();
  return ch;
  // return post;
}
Expression* Interpreter::interpret(string s) {
  Expression* v =new Value(infixtopostfix(s));
  return v;
}
void Interpreter::setVariables(string str)   {
  int i=0;


  while(i<(int)str.length()){
    string damya;
    string damyb;
//        if ((isalpha(str[0])==0)){
//            throw ("illegal variable assignment!");
//        }
//        if (isalpha(str[i])==0){
//            throw ("illegal variable assignment!");
//        }
    if (isalpha(str[i])!=0) {
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


    while (isdigit(str[i])!=0||((str[i]=='-')&&isdigit(str[i+1])!=0)) {
      damyb += str[i];
      i++;

      if((isdigit(str[i-1])!=0)&&(isdigit(str[i+1])!=0)&&((str[i])=='.')){
        damyb += str[i];
        i++;
      }
    }

    this->mymap[damya] = stod(damyb);
    if(str[i]==';'){
      i++;
    }

  }
}