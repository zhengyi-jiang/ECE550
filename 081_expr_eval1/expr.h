#include<sstream>


class Expression {
public:
  virtual std::string toString() const = 0;
  virtual ~Expression(){}
};

class NumExpression: public Expression{
private:
  long num;
public:
  
  NumExpression(long a):num(a){}
  
  virtual std::string toString() const{
    std::stringstream s;
    s << num;
    std::string temp = s.str();
    return temp;
  }
  virtual ~NumExpression(){}
};

class PlusExpression: public Expression{
  std::string lhs;
  std::string rhs;
public:
  PlusExpression(Expression *a,Expression *b):lhs(a->toString()),rhs(b->toString()){
    delete a;
    delete b;
  }
  virtual std::string toString() const{
    std::stringstream s;
    s << "(" << lhs << " + " << rhs << ")";
    std::string temp = s.str();
    return temp;
  }
  virtual ~PlusExpression(){}
};
