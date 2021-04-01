#include <iostream>
#include <fstream>
using namespace std;

void pause() {
#ifdef _WIN32
  system("pause");
#endif
}

int main(int argc, char** argv) {
  if (argc < 2) {
    cout << "Usage: " << argv[0] << " path_to_file.\n\nThis will overwrite the input file !!!\n";
    pause();
    return 1;
  }
  ifstream theFile(argv[1], ios_base::binary);
  if (theFile.bad()) {
    cout << "Error opening file " << argv[1] << endl;
    pause();
    return 2;
  }

  theFile.seekg(0, ios_base::end);
  size_t fileSize = (size_t)theFile.tellg();
  theFile.seekg(0, ios_base::beg);
  if (fileSize%2 != 0) {
    cout << "The size of file must be odd! Instead it was: " << fileSize << endl;
    pause();
    return 3;
  }
  if (fileSize == 0) {
    cout << "The file is empty.\n";
    pause();
    return 4;
  }

  char* buffer = new char[fileSize];
  theFile.read(buffer, fileSize);
  theFile.close();
  
  for (size_t i=0; i<fileSize; i+=2) {
    swap(buffer[i], buffer[i+1]);
  }

  ofstream outFile(argv[1], ios_base::binary);
  outFile.write(buffer, fileSize);
  outFile.close();

  delete[] buffer;

  return 0;
}