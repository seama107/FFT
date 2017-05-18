#include "fft.h"
#include "dft.h"
#include <iostream>
#include <complex>
#include <string>
#include <sstream>
#include <fstream>
#include <chrono>


using namespace std;

complex<double>* readDataFile(string filename, int* inputSizes, int inputIndex);

int main(int argc, char const *argv[]) {

  //Opening data files
  string smallFileName;
  string medFileName;
  string largeFileName;
  if(argc > 3) {
    smallFileName = argv[1];
    medFileName = argv[2];
    largeFileName = argv[3];
  }
  else {
    cout << "No file specified." << endl;
    smallFileName = "sigDataSmall.txt";
    medFileName = "sigDataMed.txt";
    largeFileName = "sigDataLarge.txt";
  }
  int* inputSizes = new int[3];

  complex<double>* dataSmall = readDataFile(smallFileName, inputSizes, 0);
  complex<double>* dataMed = readDataFile(medFileName, inputSizes, 1);
  complex<double>* dataLarge = readDataFile(largeFileName, inputSizes, 2);
  int smallN = inputSizes[0];
  int medN = inputSizes[1];
  int largeN = inputSizes[2];

  std::chrono::steady_clock::time_point begin;
  std::chrono::steady_clock::time_point end;

  //Calculating DFT
  cout << "Timing DFTs" << endl;

  begin = std::chrono::steady_clock::now();
  complex<double>* dftSmall = DFT(dataSmall, smallN);
  end = std::chrono::steady_clock::now();
  cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." <<endl;

/*
  begin = std::chrono::steady_clock::now();
  complex<double>* dftMed = DFT(dataMed, medN);
  end = std::chrono::steady_clock::now();
  cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." <<endl;

  begin = std::chrono::steady_clock::now();
  complex<double>* dftLarge = DFT(dataLarge, largeN);
  end = std::chrono::steady_clock::now();
  cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." <<endl;
*/

  //Calculating FFT
  cout << "Timing FFTs" << endl;

  begin = std::chrono::steady_clock::now();
  complex<double>* fftSmall = FFT(dataSmall, smallN);
  end = std::chrono::steady_clock::now();
  cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." <<endl;

  begin = std::chrono::steady_clock::now();
  complex<double>* fftMed = FFT(dataMed, medN);
  end = std::chrono::steady_clock::now();
  cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." <<endl;

  begin = std::chrono::steady_clock::now();
  complex<double>* fftLarge = FFT(dataLarge, largeN);
  end = std::chrono::steady_clock::now();
  cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " microseconds." <<endl;


  delete[] dftSmall;
  //delete[] dftMed;
  //delete[] dftLarge;
  delete[] dataSmall;
  delete[] dataMed;
  delete[] dataLarge;
  delete[] fftSmall;
  delete[] fftMed;
  delete[] fftLarge;

  return 0;
}

complex<double>* readDataFile(string filename, int* inputSizes, int inputIndex) {
  cout << "Reading " << filename << " for signal data.    ";
  //Opening data file
  ifstream inFile(filename);

  //Reading file
  string line;
  stringstream ss;
  int n;
  double sampleRate;
  try {
    getline(inFile, line);
    n = stoi(line);
    cout << "Found " << n << " data points.    ";
    getline(inFile, line);
    sampleRate = stod(line);
    cout << "sampleRate of " << sampleRate << " Hz." << endl;
  }
  catch(int e) {
    cout << "Invalid File Format." << endl;
    return 0;
  }

  //Reading data points
  complex<double>* data = new complex<double>[n];
  int i = 0;
  while (getline(inFile, line) && i < n) {
    istringstream is(line);
    is >> data[i];
    i++;
  }
  inFile.close();
  inputSizes[inputIndex] = n;
  return data;

}
