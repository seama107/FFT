#ifndef FFT_H
#define FFT_H


#include <iostream>
#include <complex>
#include <cmath>

std::complex<double>* FFT(std::complex<double>* A, int length);

template <typename T>
T* extractEveryN(T* inputArray, int size, int n, int offset) {

  int outSize = size / n - offset / n;
  if (outSize <= 0) {
    throw -1;
  }
  T* out = new T[outSize];
  int outIndex = 0;
  for (int i = 0; i < size - offset; i += n) {
    out[outIndex++] = inputArray[i + offset];
  }
  return out;
}

#endif
