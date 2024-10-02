#include <iostream>
using namespace std;

int main() {
    string binary = "";

    int num;
    cin >> num;

    int temp = num;
    while(temp > 1) {
        int rem = temp % 2;
        // cout << to_string(rem);
        binary = to_string(rem) + binary;
        temp /= 2;
    }
    binary = to_string(temp) + binary;

    cout << binary << endl;

    return 0;
}