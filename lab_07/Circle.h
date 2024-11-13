/*
 * Circle.h
 *
 *  Created on: 23 Oct 2014
 *      Author: np183
 */

#ifndef CIRCLE_H_
#define CIRCLE_H_

#include "Shape.h"
using std::string;

// Circle inherits from Shape
// It adds the option to set and get the radius
class Circle : public Shape {
public:
	// It should be impossible to create a circle without additional data
	Circle() {}
	Circle(float radius, const string& borderColor, bool fill = false, const string& fillColor = "");
	Circle(const Circle&) = default;
	~Circle() = default;

	// Setter and getter for radius
	float radius() const;
	void setRadius(float radius);

	// TODO:
	// Choose which functions to implement here
private:
	// TODO: add member variables
};

#endif /* CIRCLE_H_ */
