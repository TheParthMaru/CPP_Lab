/*
 * Shape.h
 *
 *  Originally created on: 23 Oct 2014
 *      Author: np183
 */

#ifndef SHAPE_H_
#define SHAPE_H_

#include <string>
using std::string;

// This is the base class for all the shapes
// Every shape has a border color (string)
// It is either filled or unfilled and in the case
// that it is filled it also has a fill color (string).
//
// All shapes support functions setting and checking the
// colors and whether or not they are filled.
class Shape {
public:
	// It should be impossible to create a shape without additional details
	// I am leaving this function here so that compilation of the bare
	// version I am giving students will work
	Shape() {}

	// Constructor initializing all these details
	Shape(const string& borderColor, bool fill = false, const string& fillColor = "");

	// Copy constructor (as there are no pointers here
	// you can just use the standard implementations by the compiler)
	Shape(const Shape&) = default;

	// Destructor. Again, can use default
	~Shape() = default;

	// Setter and getter for border color
	string borderColor() const;
	void setBorderColor(const string& color);

	// Setter and getter for fill
	bool fill() const;
	void setFill(bool);

	// Setter and getter for fill color
	string fillColor() const;
	void setFillColor(const string& color);

	// Functions for computing the area, perimeter
	float area() const;
	float perimeter() const;

private:
	// TODO:
	// Add private (or protected?) members.
    private:
        string borderColor;
        bool fill;
        string fillColor;

};

#endif /* SHAPE_H_ */