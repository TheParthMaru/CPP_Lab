/**
 * Perfect number
 */

#include <iostream>
using namespace std;

int main() {
    int num;
    cin >> num;

    int sum = 0;
    for(int i = 1; i <= num / 2; i++) {
        int divisor;

        if(num % i == 0) {
            divisor = i;
            sum += divisor;
        }
    }

    if(num == sum) {
        cout << "True" << endl;
    } else {
        cout << "False" << endl;
    }

    return 0;
}