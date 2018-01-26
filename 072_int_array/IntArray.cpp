#include "IntArray.h"
#include <assert.h>
#include <ostream>

IntArray::IntArray() {
  data = NULL;
  numElements = 0;
}
IntArray::IntArray(int n) {
  if(n <0){
    exit(EXIT_FAILURE);
  }
  if(n == 0){
    data = NULL;
    numElements = 0;
  }
  else{
    data = new int[n];
    numElements = n;
    for (int i = 0; i < n; i++){
      data[i]=0;
    }
  }
}

IntArray::IntArray(const IntArray & rhs)  {
  data = new int[rhs.numElements];
  numElements = rhs.numElements;
  for (int i = 0; i < rhs.numElements; i++){
    data[i]=rhs.data[i];
  }
}
IntArray::~IntArray() {
  delete[] data;
}

IntArray & IntArray::operator=(const IntArray & rhs) {
  if (this != &rhs){
    delete[] data;
    data = new int[rhs.numElements];
    numElements = rhs.numElements;
    for (int i = 0; i < rhs.numElements; i++){
      data[i]=rhs.data[i];
    }
  }
  return *this;
}

const int & IntArray::operator[](int index) const {
  assert(index < numElements && index >= 0);
  return data[index];
}

int & IntArray::operator[](int index) {
  assert(index < numElements && index >= 0);
  return data[index];
}

int IntArray::size() const {
  int ans = numElements;
  return ans;
}

bool IntArray::operator==(const IntArray & rhs) const {
  if(numElements != rhs.numElements){
    return false;
  }
  for(int i = 0 ; i < numElements ; i++){
    if(data[i] != rhs.data[i]){
      return false;
    }
  }
  return true;
}

bool IntArray::operator!=(const IntArray & rhs) const {
  if(*this == rhs){
    return false;
  }
  return true;
}

std::ostream & operator<<(std::ostream & s, const IntArray & rhs) {
  s <<"{";
  if( rhs.size() <= 0){
    s <<"}";
    return s;
  }
  for (int i = 0 ; i < rhs.size()-1 ; i++){
    s <<rhs[i]<<", ";
  }
  s <<rhs[rhs.size()-1]<<"}";
  return s;
}

