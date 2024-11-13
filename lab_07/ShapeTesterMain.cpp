/*
 * main.cpp
 */

#include <iostream>
#include <string>
#include "ShapeTester.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

int main(int argc, char* argv[]) {

	while (argc > 1) {

		switch (argv[--argc][0]) {
		case 'a':
		{
			ShapeTester t;
			t.testCtor();
		}
		break;
		case 'b':
		{
			ShapeTester t;
			t.testSimpleFunctions();
		}
		break;
		case 'c':
		{
			ShapeTester t;
			t.testArea();
		}
		break;
		case 'd':
		{
			ShapeTester t;
			t.testPerimeter();
		}
		break;
		}
	}
	return 0;
}

