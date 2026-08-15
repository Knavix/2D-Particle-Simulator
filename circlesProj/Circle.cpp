#include <iostream>
#include "Circle.h"

void Circle::setRadius(float radius) {
	this->radius = radius;
}

void Circle::handleWallCollisions(
	float leftWall,
	float rightWall,
	float topWall,
	float bottomWall
) {
	if (x + radius >= rightWall) {
		x = rightWall - radius;
		xVelocity = -xVelocity;
	}
	if (x - radius <= leftWall) {
		x = leftWall + radius;
		xVelocity = -xVelocity;
	}
	if (y + radius >= topWall) {
		y = topWall - radius;
		yVelocity = -yVelocity;
	}
	if (y - radius <= bottomWall) {
		y = bottomWall + radius;
		yVelocity = -yVelocity;
	}
}