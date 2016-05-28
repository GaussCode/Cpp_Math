/*
  Matrix.h
  
  Autor: Roland Völker
  eMail: roland_voelker@web.de
  Datum: 2016-05-27
  
  (c) Alle Rechte vorbehalten.
*/


#ifndef MATRIX_H_RV
#define MATRIX_H_RV

#define DIMENSION_EXCEPTION 1
#include <ostream>


namespace VMath
{

/*
  Matrix im Row-Major-Format. Datei enthält ansonsten sämtliche
  sinnvolle Operatoren (intern und extern bzw. global).
*/
class Matrix {
public:
  // Erstellt einen Array mit Länge 0.
  Matrix();
    
  Matrix(int m, int n);
  Matrix(double* matrix, int m, int n);    
  Matrix(const Matrix& m);  
  ~Matrix();  
  
  
  // Gibt die Anzahl der Reihen wieder.
  int getRows() const;   
  
  
  // Gibt die Anzahl der Spalten wieder.
  int getCols() const;  
  
  
  // Gibt die Einträge der Matrix wieder.
  double* getMatrix() const;
  
  
  // Die folgenden Methoden sind die einzigen,
  // die m, n und die Matrixeinträge verändern dürfen.
  void setMatrix(double* matrix, int m, int n);
  void setMatrix(int m, int n);  
  void set(int i, int j, double d);
  void set(int i, double d);
  
  
  // Gibt den Wert matrix[i] wieder.
  double operator[](int i) const;
  
  
  // Gibt den Wert der Matrix in Reihe i und Spalte j an.
  double operator()(int i, int j) const;
  
  
  Matrix& operator=(Matrix const& m);
  
  
  // Folgende Methoden nutzen die globalen Funktionen zur Berechnung.
  Matrix& operator+=(Matrix const& m);
  Matrix& operator-=(Matrix const& m);
  Matrix& operator*=(Matrix const& m);
  Matrix& operator*=(double d);
  
  
  // friend-Deklarationen der unteren Funktionen
  friend Matrix operator+(Matrix const& m1, Matrix const& m2);
  friend Matrix operator-(Matrix const& m1, Matrix const& m2);
  friend Matrix operator-(Matrix const& m);
  friend Matrix operator*(Matrix const& m1, Matrix const& m2);
  friend Matrix operator*(Matrix const& m, double d);
  friend Matrix operator*(double d, Matrix const& m);
  friend std::ostream& operator<<(std::ostream& os, Matrix const& m);
  
private:
  int m; // Zeilen
  int n; // Spalten
  
  // Matrixeinträge
  double* matrix = nullptr;
};

// Folgende Operatoren sind direkt aus der
// Linearen Algebra abgeleitet.
Matrix operator+(Matrix const& m1, Matrix const& m2);
Matrix operator-(Matrix const& m1, Matrix const& m2);
Matrix operator-(Matrix const& m);
Matrix operator*(Matrix const& m1, Matrix const& m2);
Matrix operator*(Matrix const& m, double d);
Matrix operator*(double d, Matrix const& m);
std::ostream& operator<<(std::ostream& os, Matrix const& m);

};

#endif

