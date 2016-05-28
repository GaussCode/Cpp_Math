/*
  Matrix.cpp
  
  Autor: Roland Völker
  eMail: roland_voelker@web.de
  Datum: 2016-05-27
  
  (c) Alle Rechte vorbehalten.
*/


#include "Matrix.h"
#include <iostream>

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


/*
  Gibt die Matrix mit Leerzeichen als Trennzeichen aus.
*/
void Matrix::out() const {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      std::cout << (*this)(i, j) << " ";
    }
    std::cout << std::endl;
  }
}


////////////////////////
// Globale Operatoren //
////////////////////////


Matrix operator+(Matrix const& m1, Matrix const& m2) {
  // Reihen oder Spalten stimmen nicht überein
  if (m1.getRows() != m2.getRows() || m1.getCols() != m2.getCols())
    throw DIMENSION_EXCEPTION;
   
  int len = m1.getRows() * m1.getCols();
  double* matrix = new double[len];
   
  for (int i = 0; i < len; i++) {
    matrix[i] = m1[i] + m2[i];
  }
  
  return Matrix(matrix, m1.getRows(), m1.getCols());
}


/*
  Ist das gleiche wie bei operator+, nur das "+" 
  in der Schleife wurde zu einem "-" geändert.
*/
Matrix operator-(Matrix const& m1, Matrix const& m2) {
  if (m1.getRows() != m2.getRows() || m1.getCols() != m2.getCols())
    throw DIMENSION_EXCEPTION;
   
  int len = m1.getRows() * m1.getCols();
  double* matrix = new double[len];
   
  for (int i = 0; i < len; i++) {
    matrix[i] = m1[i] - m2[i];
  }
  
  return Matrix(matrix, m1.getRows(), m1.getCols());
}


Matrix operator-(Matrix const& m) {
  int len = m.getRows() * m.getCols();
  double* matrix = new double[len];
  for (int i = 0; i < len; i++) {
    matrix[i] = -m[i];
  }
  
  return Matrix(matrix, m.getRows(), m.getCols());
}


Matrix operator*(Matrix const& m1, Matrix const& m2) {
  if (m1.getCols() != m2.getRows())
    throw DIMENSION_EXCEPTION;
  
  double* matrix = new double[m1.getRows()*m2.getCols()];
  
  for (int i = 0; i < m1.getRows(); i++) {
    for (int j = 0; j < m2.getCols(); j++) {
      double sum = 0;
      for (int k = 0; k < m1.getCols(); k++) {
        sum += m1(i, k) * m2(k, j);
      }
      matrix[i*m2.getCols()+j] = sum;
    }
  }
  
  return Matrix(matrix, m1.getRows(), m2.getCols());
}


Matrix operator*(Matrix const& m, double d) {
  int len = m.getRows() * m.getCols();
  double* matrix = new double[len];
  for (int i = 0; i < len; i++) {
    matrix[i] = d * m[i];
  }
  
  return Matrix(matrix, m.getRows(), m.getCols());
}


Matrix operator*(double d, Matrix const& m) {
  int len = m.getRows() * m.getCols();
  double* matrix = new double[len];
  for (int i = 0; i < len; i++) {
    matrix[i] = d * m[i];
  }
  
  return Matrix(matrix, m.getRows(), m.getCols());
}

