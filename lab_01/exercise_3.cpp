#include <iostream>
using namespace std;

int main() {
    int num;
    int count = 0;
    float sum = 0.0;
    do {
        cin >> num;
        if(num != 0) {
            count++;
        } 
        sum += num;

    }while(num != 0);

    float average = sum / count;
    printf("%.2f\n", average);

    return 0;
}