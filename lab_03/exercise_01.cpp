#include <iostream>
using namespace std;

int main() {
  int* intPtr = new int;
  *intPtr = 69;

  float* floatPtr = new float;
  *floatPtr = 69.69f;

  char* charPtr = new char;
  *charPtr = 's';

  string* strPtr = new string;
  *strPtr = "parth";

  cout << *intPtr << endl;
  cout << *floatPtr << endl;
  cout << *charPtr << endl;
  cout << *strPtr << endl;

  // Memory deallocation
  delete intPtr;
  delete charPtr;
  delete floatPtr;
  delete strPtr;
}
