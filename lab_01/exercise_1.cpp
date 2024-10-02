#include <iostream>
using namespace std;

int main() {
    int num;
    cin >> num;

    if(num < 0) {
        cout << "Please enter a positive number" << endl;
        return 0;
    }

    cout << num << " ";
    while(num > 1) {
        if(num % 2 != 0) {
            num = num * 3 + 1;
        } else {
            num /= 2;
        }

        cout << num << " ";
    }

    cout << endl;
}