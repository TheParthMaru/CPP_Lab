#include <iostream>
using namespace std;

void swapPointer(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void swapRef(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

int main() {
    int a = 69;
    int b = 96;

    swapPointer(&a, &b);

    cout << a << " " << b << endl;

    swapRef(a, b);
    cout << a << " " << b << endl;

    return 0;
}