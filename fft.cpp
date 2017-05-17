#include "fft.h"

using namespace std;

const complex<double> I( 0,1 );

complex<double>* FFT(complex<double>* A, int length){
  complex<double>* Y = new complex<double>[length];

  
  if(length == 1) {
    Y[0] = A[0];
    return Y;
  }

  //Creating the output vector

  //Splitting up the input
  complex<double>* A_even;
  complex<double>* A_odd;
  try {
    A_even = extractEveryN(A, length, 2, 0);
    A_odd = extractEveryN(A, length, 2, 1);
  }
  catch(int e){
    if(e == -1) {
      cout << "Tried to split up an array that was too small" << endl;
      cout << "Array is currently at length " << length << endl;
      for(int i = 0; i < length; i++) {
        cout << A[i] << "\t";
      }
    }
  }

  //Recursive step
  complex<double>* Y_even = FFT(A_even, length / 2);
  complex<double>* Y_odd = FFT(A_odd, length / 2);

  delete[] A_even;
  delete[] A_odd;

  //Recombining

  complex<double> omega_n = cos(2 * M_PI/ double(length)) + I * sin(2 * M_PI/ double(length));
  complex<double> omega(1,0);

  for (int k = 0; k < length / 2; k++) {
    Y[k] = Y_even[k] + omega * Y_odd[k];
    Y[k + length / 2] = Y_even[k] - omega * Y_odd[k];
    omega = omega * omega_n;
  }
  delete[] Y_even;
  delete[] Y_odd;

  return Y;
}
