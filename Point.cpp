#include "Point.h"
#include<iostream>
using namespace std;

Point::Point()
{
	x = 0;
	y = 0;
}


Point::Point(float x, float y)
{
	this->x = x;
	this->y = y;
}
void Point::put(float x, float y) {
	this->x = x;
	this->y = y;
}

Point::~Point()
{}

void Point::showData()
{
	cout << x << " " << y << endl;
}
float Point::getX(){
	return x;
}
float Point::getY() {
	return y;
}
void Point::setX(float x) {
	this->x = x;
}
void Point::setY(float) {
	this->y = y;
}