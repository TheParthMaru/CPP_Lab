/*
 * ShapeTester.h
 *
 *  Created on: 23 Oct 2014
 *      Author: np183
 */

#ifndef SHAPETESTER_H_
#define SHAPETESTER_H_

#include <string>

class ShapeTester {
public:
	ShapeTester();
	~ShapeTester();

	void testCtor();
	void testSimpleFunctions();
	void testArea();
	void testPerimeter();
private:
	void errorOut_(const std::string& errMsg, unsigned int errBit);
	bool errorSet_(unsigned int mask);
	void passOut_(const std::string& passMsg);

	char error_;
	std::string funcname_;
};

#endif /* SHAPETESTER_H_ */