#include <stdlib.h>
#include <math.h>
#include "circle.h"

Circle::Circle(Point c, double r): center(c), r(r){
}

void Circle::move(double dx, double dy){
  center.move(dx,dy);
}

double Circle::intersectionArea(const Circle & otherCircle){
  double inter = 0;
  double d = center.distanceFrom(otherCircle.center);
  if(d >= (r + otherCircle.r)){
    return inter;
  }
  if(d <= (r - otherCircle.r)){
    return otherCircle.r*otherCircle.r*M_PI;
  }
  if(d <= (otherCircle.r - r)){
    return r*r*M_PI;
  }
  
  double round = (r + otherCircle.r + d)/2;
  double tS = 2*sqrt(round*(round-d)*(round-r)*(round-otherCircle.r));
  double csa = acos((otherCircle.r*otherCircle.r+d*d-r*r)/(2*otherCircle.r*d))*otherCircle.r*otherCircle.r;
  double csb = acos((r*r+d*d-otherCircle.r*otherCircle.r)/(2*r*d))*r*r;
  return csa+csb-tS;
}
