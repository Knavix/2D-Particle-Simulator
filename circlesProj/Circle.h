#ifndef CIRCLE_H
#define CIRCLE_H
#include <iostream>

struct Circle {
	float x;
	float y;
	float radius;

	float xVelocity;
	float yVelocity;

	void setRadius(float radius);

	void handleWallCollisions(
		float leftWall,
		float rightWall,
		float topWall,
		float bottomWall
	);
};



#endif
