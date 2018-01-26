#include<sstream>


class Expression {
public:
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
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
  virtual long evaluate() const{
    return num;
  }
  
  
  virtual ~NumExpression(){}
};

class CalculationExpression: public Expression{
protected:
  std::string lhs;
  std::string rhs;
  long lhsN;
  long rhsN;
public:
 CalculationExpression(Expression *a,Expression *b):lhs(a->toString()),rhs(b->toString()),lhsN(a->evaluate()),rhsN(b->evaluate()){
    delete a;
    delete b;
  }
  virtual ~CalculationExpression(){}
};

class PlusExpression: public CalculationExpression{
public:
  PlusExpression(Expression *a,Expression *b):CalculationExpression(a,b){}
  virtual std::string toString() const{
    std::stringstream s;
    s << "(" << lhs << " + " << rhs << ")";
    std::string temp = s.str();
    return temp;
  }
  virtual long evaluate() const{
    long ans = lhsN + rhsN;
    return ans;
  }
  
  virtual ~PlusExpression(){}
};

class MinusExpression: public CalculationExpression{
public:
  MinusExpression(Expression *a,Expression *b):CalculationExpression(a,b){}
  virtual std::string toString() const{
    std::stringstream s;
    s << "(" << lhs << " - " << rhs << ")";
    std::string temp = s.str();
    return temp;
  }
  virtual long evaluate() const{
    long ans = lhsN - rhsN;
    return ans;
  }
  
  virtual ~MinusExpression(){}
};

class TimesExpression: public CalculationExpression{
public:
 TimesExpression(Expression *a,Expression *b):CalculationExpression(a,b){}
  virtual std::string toString() const{
    std::stringstream s;
    s << "(" << lhs << " * " << rhs << ")";
    std::string temp = s.str();
    return temp;
  }
  
  virtual long evaluate() const{
    long ans = lhsN * rhsN;
    return ans;
  }
  
  virtual ~TimesExpression(){}
};

class DivExpression: public CalculationExpression{
public:
 DivExpression(Expression *a,Expression *b):CalculationExpression(a,b){}
  virtual std::string toString() const{
    std::stringstream s;
    s << "(" << lhs << " / " << rhs << ")";
    std::string temp = s.str();
    return temp;
  }
  
  virtual long evaluate() const{
    long ans = lhsN/ rhsN;
    return ans;
  }
  virtual ~DivExpression(){}
};
