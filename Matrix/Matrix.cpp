/*
  Matrix.cpp
  
  Autor: Roland Völker
  eMail: roland_voelker@web.de
  Datum: 2016-05-28
  Version: 2
  
  (c) Alle Rechte vorbehalten.
*/


#include "Matrix.h"


namespace VMath
{

Matrix::Matrix() {
  setMatrix(0, 0);
}


Matrix::Matrix(int m, int n) {
  setMatrix(m, n);
}


Matrix::Matrix(double* data, int m, int n) {
  setMatrix(data, m, n);
}


Matrix::Matrix(Matrix const& m) {
  setMatrix(m.data, m.m, m.n);
}


Matrix::~Matrix() {
  if (data != nullptr)
    delete[] data;
}


int Matrix::getRows() const {
  return m;
}


int Matrix::getCols() const {
  return n;
}


/*
  Gibt eine tiefe Kopie der Matrix zurück.
*/
double* Matrix::getMatrix() const {
  double* res = new double[m*n];
  for (int i = 0; i < m*n; i++) {
    res[i] = data[i];
  }
  
  return res;
}


void Matrix::setMatrix(int m, int n) {
  if (data != nullptr)
    delete[] data;

  this->m = m;
  this->n = n;
  data = new double[m*n];
  
  for (int i = 0; i < m*n; i++) {
    data[i] = 0;
  }
}


/*
  Legt eine normale tiefe Kopie vom angegebenen Array an.
*/
void Matrix::setMatrix(double* data, int m, int n) {
  if (this->data != nullptr)
    delete[] data;

  this->m = m;
  this->n = n;
  this->data = new double[m*n];
  
  for (int i = 0; i < m*n; i++) {
    this->data[i] = data[i];
  }
}


void Matrix::set(int i, int j, double d) {
  data[i*n+j] = d;
}


void Matrix::set(int i, double d) {
  data[i] = d;
}


double Matrix::operator[](int i) const {
  return data[i];
}


double Matrix::operator()(int i, int j) const {
  return data[i*n + j];
}


Matrix& Matrix::operator=(Matrix const& m) {
  if (data != nullptr)
    delete[] data;
    
  setMatrix(m.data, m.m, m.n);
  
  return *this;
}


Matrix& Matrix::operator+=(Matrix const& m) {
  *this = (*this) + m;  
  return *this;
}


Matrix& Matrix::operator-=(Matrix const& m) {
  *this = (*this) - m;  
  return *this;
}


Matrix& Matrix::operator*=(Matrix const& m) {
  *this = (*this) * m;  
  return *this;
}


Matrix& Matrix::operator*=(double d) {
  *this = (*this) * d;  
  return *this;
}


////////////////////////
// Globale Operatoren //
////////////////////////


Matrix operator+(Matrix const& m1, Matrix const& m2) {
  // Reihen oder Spalten stimmen nicht überein
  if (m1.m != m2.n || m1.m != m2.n)
    throw DIMENSION_EXCEPTION;
   
  int len = m1.m * m1.n;
  double* data = new double[len];
   
  for (int i = 0; i < len; i++) {
    data[i] = m1[i] + m2[i];
  }
  
  return Matrix(data, m1.m, m1.n);
}


/*
  Ist das gleiche wie bei operator+, nur das "+" 
  in der Schleife wurde zu einem "-" geändert.
*/
Matrix operator-(Matrix const& m1, Matrix const& m2) {
  if (m1.m != m2.m || m1.n != m2.n)
    throw DIMENSION_EXCEPTION;
   
  int len = m1.m * m1.n;
  double* data = new double[len];
   
  for (int i = 0; i < len; i++) {
    data[i] = m1[i] - m2[i];
  }
  
  return Matrix(data, m1.m, m1.n);
}


Matrix operator-(Matrix const& m) {
  int len = m.m * m.n;
  double* data = new double[len];
  for (int i = 0; i < len; i++) {
    data[i] = -m[i];
  }
  
  return Matrix(data, m.m, m.n);
}


Matrix operator*(Matrix const& m1, Matrix const& m2) {
  if (m1.n != m2.m)
    throw DIMENSION_EXCEPTION;
  
  double* data = new double[m1.m*m2.n];
  
  for (int i = 0; i < m1.m; i++) {
    for (int j = 0; j < m2.n; j++) {
      double sum = 0;
      for (int k = 0; k < m1.n; k++) {
        sum += m1(i, k) * m2(k, j);
      }
      data[i*m2.n+j] = sum;
    }
  }
  
  return Matrix(data, m1.m, m2.n);
}


Matrix operator*(Matrix const& m, double d) {
  int len = m.m * m.n;
  double* data = new double[len];
  for (int i = 0; i < len; i++) {
    data[i] = d * m[i];
  }
  
  return Matrix(data, m.m, m.n);
}


Matrix operator*(double d, Matrix const& m) {
  int len = m.m * m.n;
  double* data = new double[len];
  for (int i = 0; i < len; i++) {
    data[i] = d * m[i];
  }
  
  return Matrix(data, m.m, m.n);
}


/*
  Gibt die Matrix mit Leerzeichen als Trennzeichen aus.
*/
std::ostream& operator<<(std::ostream& os, Matrix const& m) {
  for (int i = 0; i < m.m; i++) {
    for (int j = 0; j < m.n; j++) {
      os << m(i, j) << " ";
    }
    
    // Einen abschließenden Zeilenumbruch gibt es nicht
    if (i < m.m-1) os << "\n";
  }
  
  return os;
}

};

