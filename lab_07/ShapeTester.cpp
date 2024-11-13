/*
 * ShapeTester.cpp
 *
 *  Created on: 23 Oct 2014
 *      Author: np183
 */

#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <iomanip>
#include <utility>
#include <sstream>
#include <memory>

#include "ShapeTester.h"
#include "Shape.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Square.h"

// # define M_PI           3.14159265358979323846  /* pi */
// already in math.h

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::stringstream;
using std::unique_ptr;

ShapeTester::ShapeTester() : error_(false), funcname_() {
  unsigned int val(time(0)*rand());
  cout << val << endl;
  srand(val);
}

ShapeTester::~ShapeTester() {
}

void ShapeTester::testCtor(){
  funcname_ = "testCtor";

  Circle oc(1.0,"red",false,"black");
  Rectangle orr(1.0,2.0,"blue",true,"green");
  Square os(3.0,"purple",false,"pink");
  Shape& c(oc);
  Shape& r(orr);
  Shape& s(os);

  if (c.fill() || c.borderColor()!="red" || c.fillColor()!="black"  ||
      !r.fill() || r.borderColor()!="blue" || r.fillColor()!="green" ||
      s.fill() || s.borderColor()!="purple" || s.fillColor()!="pink") {
    errorOut_("something went wrong with contructor",0);
  }

  if (oc.radius() != 1.0) {
    errorOut_("radius of circle is wrong",1);
  }

  if (orr.width()!=1.0 || orr.height()!=2.0) {
    errorOut_("width or length of rectangle is wrong",2);
  }

  Rectangle& ss(os);
  if (ss.width()!=3.0 || ss.height()!=3.0) {
    errorOut_("width or length of square is wrong",3);
  }
  
  passOut_("Did some tests on the constructors");
}

void ShapeTester::testSimpleFunctions() {
  funcname_ = "testSimpleFunctions";

  Circle oc(1.0,"red",false,"black");
  Rectangle orr(1.0,2.0,"blue",true,"green");
  Square os(3.0,"purple",false,"pink");
  Shape& c(oc);
  Shape& r(orr);
  Shape& s(os);

  if (c.fill() || c.borderColor()!="red" || c.fillColor()!="black" ||
      !r.fill() || r.borderColor()!="blue" || r.fillColor()!="green" ||
      s.fill() || s.borderColor()!="purple" || s.fillColor()!="pink") {
    errorOut_("something went wrong with contructor",0);
  }

  if (oc.radius() != 1.0) {
    errorOut_("radius of circle is wrong",1);
  }

  if (orr.width()!=1.0 || orr.height()!=2.0) {
    errorOut_("width or length of rectangle is wrong",2);
  }

  Rectangle& ss(os);
  if (ss.width()!=3.0 || ss.height()!=3.0) {
    errorOut_("width or length of square is wrong",3);
  }

  c.setFill(true);
  c.setBorderColor("black");
  c.setFillColor("red");
  oc.setRadius(2.0);

  if (!c.fill() || c.borderColor()!="black" || c.fillColor()!="red" ||
      oc.radius() != 2.0) {
    errorOut_("circle functions setters not working",0);
  }

  r.setFill(false);
  r.setBorderColor("green");
  r.setFillColor("blue");
  orr.setWidth(3.0);
  orr.setHeight(4.0);

  if (r.fill() || r.borderColor()!="green" || r.fillColor()!="blue" ||
      orr.width()!=3.0 || orr.height()!=4.0) {
    errorOut_("rectangle functions setters not working",1);
  }
  
  s.setFill(true);
  s.setBorderColor("pink");
  s.setFillColor("purple");
  ss.setHeight(5.0);

  if (!s.fill() || s.borderColor()!="pink" || s.fillColor()!="purple" ||
      ss.height()!=5.0 || ss.width()!=5.0) {
    errorOut_("square functions setters not working",2);
  }
  else {
    ss.setWidth(6.0);
    if (ss.height()!=6.0 || ss.width()!=6.0) {
      errorOut_("square functions setters not working",2);
    }
  }
  passOut_("tested the basic setters and getters");
}

void ShapeTester::testArea() {
  funcname_ = "testArea";

  Circle oc(1.0,"red",false,"black");
  Rectangle orr(1.0,2.0,"blue",true,"green");
  Square os(3.0,"purple",false,"pink");
  Shape& c(oc);
  Shape& r(orr);
  Shape& s(os);

  if (r.area()!=2.0)
    errorOut_("Rectangle area wrong",0);
  if (s.area()!=9.0)
    errorOut_("Square area wrong",1);
  if (c.area() - M_PI > 0.00001 ||
      M_PI - c.area() > 0.00001)
    errorOut_("Circle area wrong",2);

  passOut_("Area computation tested");
}

void ShapeTester::testPerimeter() {
  funcname_ = "testPerimeter";

  Circle oc(1.0,"red",false,"black");
  Rectangle orr(1.0,2.0,"blue",true,"green");
  Square os(3.0,"purple",false,"pink");
  Shape& c(oc);
  Shape& r(orr);
  Shape& s(os);

  if (r.perimeter()!=6.0)
    errorOut_("Rectangle perimeter wrong",0);
  if (s.perimeter()!=12.0)
    errorOut_("Square perimeter wrong",1);
  if (c.perimeter() - 2.0*M_PI >= 0.00002 ||
      2.0*M_PI - c.perimeter() >= 0.00002)
    errorOut_("Circle perimeter wrong",2);

  passOut_("did some things");
}


void ShapeTester::errorOut_(const string& errMsg, unsigned int errBit) {
        cerr << funcname_ << " " << "(fail";
        if (errBit)
                cerr << errBit;
        cerr << "): " << errMsg << endl;
        error_|=(1<<errBit);
}

bool ShapeTester::errorSet_(unsigned int mask) {
        return error_& mask;
}

void ShapeTester::passOut_(const string& passMsg) {
        if (!error_) {
                cerr << funcname_ << " " << "(pass): " << passMsg << endl;
        }
}