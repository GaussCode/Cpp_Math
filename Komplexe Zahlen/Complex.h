/*
  Complex.h
  
  Autor: Roland Völker
  eMail: roland_voelker@web.de
  Datum: 2016-05-28
  
  (c) Alle Rechte vorbehalten.
*/


#ifndef COMPLEX_H_RV
#define COMPLEX_H_RV

#include <ostream>


namespace VMath
{

/*
  Definiert eine komplexe Zahl durch kartesische Koordinaten
  auf der Gaußschen Zahlenebene.
*/
class Complex {
public:
  Complex();
  Complex(double re);
  Complex(double re, double im);
  Complex(Complex const& c);

  double abs2() const;
  double abs() const;
  double arg() const;
  Complex conj() const;
  
  void setRe(double re);
  void setIm(double im);
  double Re() const;
  double Im() const;
  
  Complex& operator=(Complex const& c);
  
  Complex& operator+=(Complex const& c);
  Complex& operator-=(Complex const& c);
  Complex& operator*=(double d);
  Complex& operator*=(Complex const& c);
  Complex& operator/=(double d);
  Complex& operator/=(Complex const& c);
  
  /*
    friend-Deklarierungen der unteren Funktionen.
  */  
  friend Complex operator+(Complex const& c1, Complex const& c2);
  friend Complex operator-(Complex const& c1, Complex const& c2);
  friend Complex operator-(Complex const& c);
  friend Complex operator*(Complex const& c, double d);
  friend Complex operator*(double d, Complex const& c);
  friend Complex operator*(Complex const& c1, Complex const& c2);
  friend Complex operator/(Complex const& c, double d);
  friend Complex operator/(double d, Complex const& c);
  friend Complex operator/(Complex const& c1, Complex const& c2);
  friend std::ostream& operator<<(std::ostream& os, Complex const& c);
  
private:
  double re;
  double im;
};

Complex operator+(Complex const& c1, Complex const& c2);
Complex operator-(Complex const& c1, Complex const& c2);
Complex operator-(Complex const& c);
Complex operator*(Complex const& c, double d);
Complex operator*(double d, Complex const& c);
Complex operator*(Complex const& c1, Complex const& c2);
Complex operator/(Complex const& c, double d);
Complex operator/(double d, Complex const& c);
Complex operator/(Complex const& c1, Complex const& c2);
std::ostream& operator<<(std::ostream& os, Complex const& c);

// Das mathematische i mit i^2 = -1
const Complex i__(0, 1);

};

#endif

