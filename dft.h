#ifndef DFT_H
#define DFT_H


#include <iostream>
#include <complex>
#include <cmath>

using namespace std;

const complex<double> I( 0,1 );

complex<double>* DFT(complex<double>* A, int length) {
  complex<double>* Y = new complex<double>[length];
  complex<double> omega_n = cos(2 * M_PI/ double(length)) + I * sin(2 * M_PI/ double(length));

  for(int k = 0; k < length; k++) {
    for(int j = 0; j < length; j++) {
      Y[k] += A[j] * pow(omega_n, k * j);
    }
  }
  return Y;
}

#endif
