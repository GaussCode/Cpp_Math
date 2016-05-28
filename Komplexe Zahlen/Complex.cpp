/*
  Complex.cpp
  
  Autor: Roland Völker
  eMail: roland_voelker@web.de
  Datum: 2016-05-28
  
  (c) Alle Rechte vorbehalten.
*/


#include "Complex.h"
#include <cmath>


namespace VMath
{

Complex::Complex() {
  setRe(0);
  setIm(0);
}


Complex::Complex(double re) {
  setRe(re);
  setIm(0);
}


Complex::Complex(double re, double im) {
  setRe(re);
  setIm(im);
}


Complex::Complex(Complex const& c) {
  setRe(c.re);
  setIm(c.im);
}


double Complex::abs2() const {
  return re*re + im*im;
}


double Complex::abs() const {
  return std::sqrt(re*re + im*im);
}


double Complex::arg() const {
  return std::atan2(im, re);
}


Complex Complex::conj() const {
  return Complex(re, -im);
}


void Complex::setRe(double re) {
  this->re = re;
}


void Complex::setIm(double im) {
  this->im = im;
}


double Complex::Re() const {
  return re;
}


double Complex::Im() const {
  return im;
}


Complex& Complex::operator=(Complex const& c) {
  setRe(c.re);
  setIm(c.im);
  
  return *this;
}


Complex& Complex::operator+=(Complex const& c) {
  *this = (*this) + c;
  return *this;
}


Complex& Complex::operator-=(Complex const& c) {
  *this = (*this) - c;
  return *this;
}


Complex& Complex::operator*=(double d) {
  *this = (*this) * d;
  return *this;
}


Complex& Complex::operator*=(Complex const& c) {
  *this = (*this) * c;
  return *this;
}


Complex& Complex::operator/=(double d) {
  *this = (*this) / d;
  return *this;
}

Complex& Complex::operator/=(Complex const& c) {
  *this = (*this) / c;
  return *this;
}


////////////////////////
// Globale Operatoren //
////////////////////////

Complex operator+(Complex const& c1, Complex const& c2) {
  return Complex(c1.re + c2.re, c1.im + c2.im);
}


Complex operator-(Complex const& c1, Complex const& c2) {
  return Complex(c1.re - c2.re, c1.im - c2.im);
}


Complex operator-(Complex const& c) {
  return Complex(-c.re, -c.im);
}


Complex operator*(Complex const& c, double d) {
  return Complex(c.re*d, c.im*d);
}


Complex operator*(double d, Complex const& c) {
  return Complex(c.re*d, c.im*d);
}


Complex operator*(Complex const& c1, Complex const& c2) {
  return Complex(
    c1.re*c2.re - c1.im*c2.im,
    c1.im*c2.im + c1.im*c2.re);
}


Complex operator/(Complex const& c, double d) {
  return Complex(c.re/d, c.im/d);
}


Complex operator/(double d, Complex const& c) {
  return Complex(c.re/d, c.im/d);
}


Complex operator/(Complex const& c1, Complex const& c2) {
  return c1*c2.conj() / c2.abs2();
}

std::ostream& operator<<(std::ostream& os, Complex const& c) {
  // Der Einfachheit halber werden alle
  // möglichen Fälle stupide durchgegangen
  if (c.re == 0) {
    if (c.im == 0) {
      os << 0;
    } else if (c.im == -1) {
      os << "-i";
    } else if (c.im < 0) {
      os << "-" << -c.im << "i";
    } else if (c.im == 1) {
      os << "i";
    } else if (c.im > 0) {
      os << c.im << "i";
    }
  } else {
    if (c.im == 0) {
      os << c.re;
    } else if (c.im == -1) {
      os << c.re << " - i";
    } else if (c.im < 0) {
      os << c.re << " - " << -c.im << "i";
    } else if (c.im == 1) {
      os << c.re << " + i";
    } else if (c.im > 0) {
      os << c.re << " + " << c.im << "i";
    }
  }
  
  return os;
}

};

