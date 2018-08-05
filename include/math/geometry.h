#pragma once

class Vec2d {
public:
	double x, y;
	Vec2d() :x(0), y(0) {};
	Vec2d(double x, double y) :x(x), y(y) {};
    Vec2d diff(Vec2d sub) {
        return Vec2d(x - sub.x, y - sub.y);
    }
};

class Rect {
public:
	double x, y;
	double w, h;
	Rect() : x(0), y(0), w(0), h(0) {};
	Rect(double x, double y, double w, double h) : x(x), y(y), w(w), h(h) {};
    Vec2d getCenter() {
        return Vec2d(x + h * 0.5, y + h * 0.5);
    }
};

int isRectIntersect(Rect r1, Rect r2);
int isRectInside(Rect inside, Rect outside);

Vec2d getDisplacementVector(Rect r1, Rect r2);

