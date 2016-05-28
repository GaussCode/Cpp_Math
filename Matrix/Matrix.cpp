/*
  Matrix.cpp
  
  Autor: Roland Völker
  eMail: roland_voelker@web.de
  Datum: 2016-05-27
  
  (c) Alle Rechte vorbehalten.
*/


#include "Matrix.h"
#include <iostream>

namespace VMath
{

Matrix::Matrix() {
  setMatrix(0, 0);
}


Matrix::Matrix(int m, int n) {
  setMatrix(m, n);
}


Matrix::Matrix(double* matrix, int m, int n) {
  setMatrix(matrix, m, n);
}


Matrix::Matrix(Matrix const& m) {
  setMatrix(m.matrix, m.m, m.n);
}


Matrix::~Matrix() {
  if (this->matrix != nullptr)
    delete[] matrix;
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
    res[i] = matrix[i];
  }
  
  return res;
}


void Matrix::setMatrix(int m, int n) {
  if (this->matrix != nullptr)
    delete[] matrix;

  this->m = m;
  this->n = n;
  this->matrix = new double[m*n];
  
  for (int i = 0; i < m*n; i++) {
    this->matrix[i] = 0;
  }
}


/*
  Legt eine normale tiefe Kopie vom angegebenen Array an.
*/
void Matrix::setMatrix(double* matrix, int m, int n) {
  if (this->matrix != nullptr)
    delete[] matrix;

  this->m = m;
  this->n = n;
  this->matrix = new double[m*n];
  
  for (int i = 0; i < m*n; i++) {
    this->matrix[i] = matrix[i];
  }
}


void Matrix::set(int i, int j, double d) {
  this->matrix[i*n+j] = d;
}


void Matrix::set(int i, double d) {
  this->matrix[i] = d;
}


double Matrix::operator[](int i) const {
  return matrix[i];
}


double Matrix::operator()(int i, int j) const {
  return matrix[i*n + j];
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


Matrix& Matrix::operator=(Matrix const& m) {
  if (this->matrix != nullptr)
    delete[] matrix;
    
  setMatrix(m.matrix, m.m, m.n);
  
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
  double* matrix = new double[len];
   
  for (int i = 0; i < len; i++) {
    matrix[i] = m1[i] + m2[i];
  }
  
  return Matrix(matrix, m1.m, m1.n);
}


/*
  Ist das gleiche wie bei operator+, nur das "+" 
  in der Schleife wurde zu einem "-" geändert.
*/
Matrix operator-(Matrix const& m1, Matrix const& m2) {
  if (m1.m != m2.m || m1.n != m2.n)
    throw DIMENSION_EXCEPTION;
   
  int len = m1.m * m1.n;
  double* matrix = new double[len];
   
  for (int i = 0; i < len; i++) {
    matrix[i] = m1[i] - m2[i];
  }
  
  return Matrix(matrix, m1.m, m1.n);
}


Matrix operator-(Matrix const& m) {
  int len = m.m * m.n;
  double* matrix = new double[len];
  for (int i = 0; i < len; i++) {
    matrix[i] = -m[i];
  }
  
  return Matrix(matrix, m.m, m.n);
}


Matrix operator*(Matrix const& m1, Matrix const& m2) {
  if (m1.n != m2.m)
    throw DIMENSION_EXCEPTION;
  
  double* matrix = new double[m1.m*m2.n];
  
  for (int i = 0; i < m1.m; i++) {
    for (int j = 0; j < m2.n; j++) {
      double sum = 0;
      for (int k = 0; k < m1.n; k++) {
        sum += m1(i, k) * m2(k, j);
      }
      matrix[i*m2.n+j] = sum;
    }
  }
  
  return Matrix(matrix, m1.m, m2.n);
}


Matrix operator*(Matrix const& m, double d) {
  int len = m.m * m.n;
  double* matrix = new double[len];
  for (int i = 0; i < len; i++) {
    matrix[i] = d * m[i];
  }
  
  return Matrix(matrix, m.m, m.n);
}


Matrix operator*(double d, Matrix const& m) {
  int len = m.m * m.n;
  double* matrix = new double[len];
  for (int i = 0; i < len; i++) {
    matrix[i] = d * m[i];
  }
  
  return Matrix(matrix, m.m, m.n);
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


