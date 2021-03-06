#include "IntMatrix.h"

IntMatrix::IntMatrix():numRows(0),numColumns(0),rows(NULL){}

IntMatrix::IntMatrix(int r, int c){
  if(r < 0 || c < 0){
    exit(EXIT_FAILURE);
  }
  if( r == 0 ){
    numRows = 0;
    numColumns = c;
    rows = NULL;
  }
  else{
    numRows = r;
    numColumns = c;
    rows = new IntArray*[r];
    for(int i = 0; i < r; i++){
      rows[i] = new IntArray(c);
    }
  }
}

IntMatrix::IntMatrix(const IntMatrix & rhs)  {
  numRows = rhs.numRows;
  numColumns = rhs.numColumns;
  rows = new IntArray*[rhs.numRows];
  for(int i = 0; i < numRows; i++){
    rows[i] = new IntArray(rhs.numColumns);
  }
  for(int i = 0 ; i < numRows ; i++){
    *(rows[i]) = *(rhs.rows[i]);
  }
}


IntMatrix::~IntMatrix() {
  for(int i = 0; i < numRows; i++){
    delete rows[i];
  }
  delete[] rows;
}

IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
  if(*this == rhs){
  }
  else{
    for(int i = 0; i < numRows; i++){
      delete rows[i];
    }
    delete[] rows;
    numRows = rhs.numRows;
    numColumns = rhs.numColumns;
    rows = new IntArray*[rhs.numRows];
    for(int i = 0; i < numRows; i++){
      rows[i] = new IntArray(rhs.numColumns);
    }
    for(int i = 0 ; i < numRows ; i++){
      *(rows[i]) = *(rhs.rows[i]);
    }
  }
  return *this;
}

int IntMatrix::getRows() const {
  return numRows;
}

int IntMatrix::getColumns() const {
  return numColumns;
}

const IntArray & IntMatrix::operator[](int index) const {
  assert(index < numRows && index >= 0);
  return *rows[index];
}

IntArray & IntMatrix::operator[](int index){
  assert(index < numRows && index >= 0);
  return *rows[index];
}


bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if(numColumns != rhs.numColumns || numRows != rhs.numRows){
    return false;
  }
  for(int i = 0; i < rhs.numRows; i++){
    if(*rows[i] != *rhs.rows[i]){
      return false;
    }
  }
  return true;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numColumns == rhs.numColumns && numRows == rhs.numRows);
  IntMatrix a(numRows,numColumns);
  for(int i = 0; i < numRows; i++){
    for(int j = 0; j < numColumns; j++){
      a[i][j] = (*this)[i][j] + rhs[i][j];
    }
  }
  return a;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  if(rhs.getRows() == 0){
    s<<"[  ]";
    return s;
  }
  s<<"[ ";
  for(int i = 0; i < rhs.getRows()-1; i++){
    s<<rhs[i]<<",\n";
  }
  s<<rhs[rhs.getRows()-1]<<" ]";
  return s;
}
