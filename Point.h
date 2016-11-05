#pragma once
class Point
{
private:
	float x;
	float y;
public:
	Point();
	Point(float, float);
	~Point();
	
	void put(float, float);
	void showData();
	float getX();
	float getY();
	void setX(float);
	void setY(float);

};

