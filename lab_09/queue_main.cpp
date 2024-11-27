#include <iostream>
#include <string>
#include "Queue.h"
using namespace std;

int main() {

	Queue<int> iq;
	iq.insert(1);
	iq.printAll();
	iq.insert(2);
	iq.printAll();
	iq.insert(3);
	iq.printAll();
	iq.insert(4);
	iq.printAll();
	iq.remove();
	iq.printAll();
	iq.remove();
	iq.printAll();
	iq.remove();
	iq.printAll();
	iq.insert(5);
	iq.printAll();
	iq.insert(6);
	iq.printAll();
	iq.insert(7);
	iq.printAll();
	iq.insert(8);
	iq.printAll();

	Queue<string> sq(10);
	sq.insert("hello world");
	sq.printAll();
	cout << sq.remove() << endl;
	sq.printAll();
	cout << sq.remove() << endl;
	sq.printAll();

}
