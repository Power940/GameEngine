#pragma once

#ifndef RECT2D_H
#define RECT2D_H

struct Point;

class Rect2D
{
protected:
	float m_x1; float m_y1;
	float m_x2; float m_y2;

public:
	Rect2D(float x1, float y1, float x2, float y2);
	Point Point1() const;
	Point Point2() const;
	float X1() const;
	float Y1() const;
	float X2() const;
	float Y2() const;
	float W() const;
	float H() const;
	void Update(float x1, float y1, float x2, float y2);
	void X1(float val);
	void Y1(float val);
	void X2(float val);
	void Y2(float val);
	void X(float val);
	void Y(float val);
};

#endif