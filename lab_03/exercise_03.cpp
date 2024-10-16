#include <iostream>
using namespace std;

void printArray(int* arr, int size) {
    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void printArray(string* arr, int size) {
    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    int* intArray = new int[7];
    
    cout << "Taking array inputs" << endl;
    for(int i = 0; i < 7; i++) {
        cin >> intArray[i];
    }
    printArray(intArray, 7);

    cout << "Taking string inputs" << endl;
    string* languages = new string[5];

    for(int i = 0; i < 5; i++) {
        cin >> languages[i];
    }
    
    printArray(languages, 5);
    return 0;
}