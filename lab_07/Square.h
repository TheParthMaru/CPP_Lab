/*
 * Square.h
 *
 *  Created on: 23 Oct 2014
 *      Author: np183
 */

#ifndef SQUARE_H_
#define SQUARE_H_

using std::string;

// Squre inherits from Rectangle
// Override the necessary functions
class Square {
public:
	// It should be impossible to create a square without additional info
	Square() {}
	Square(float side, const string& borderColor, bool fill = false, const string& fillColor = "");
	Square(const Square& other) = default;
	~Square() = default;

	// Choose which functions to implement here
};

#endif /* SQUARE_H_ */
