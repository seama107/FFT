#include "fft.h"
#include <iostream>
#include <complex>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;

complex<double>* readDataFile(string filename, int* inputSizes, int inputIndex);

int main(int argc, char const *argv[]) {

  //Opening data file
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

  //Calculating FFT
  complex<double>* fft_out = FFT(dataSmall, smallN);

  delete[] dataSmall;
  delete[] dataMed;
  delete[] dataLarge;
  delete[] fft_out;

  return 0;
}

complex<double>* readDataFile(string filename, int* inputSizes, int inputIndex) {
  cout << endl << "Reading " << filename << " for signal data." << endl << endl;
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
    cout << "Found " << n << " data points." << endl;
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
