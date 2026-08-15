#include <iostream>
#include <cmath>
#include "Collision.h"

bool areCirclesColliding(Circle& circle1, Circle& circle2) {

	// Distance
	float xDifference = circle2.x - circle1.x;
	float yDifference = circle2.y - circle1.y;

	float distance = sqrt(xDifference * xDifference + yDifference * yDifference);

	float combinedRadii = circle1.radius + circle2.radius;

	if (distance <= combinedRadii) {
		return true;
	}
	return false;

}
void repelCircles(Circle& circle1, Circle& circle2) {
	float xDifference = circle2.x - circle1.x;
	float yDifference = circle2.y - circle1.y;

	float distance = sqrt(xDifference * xDifference + yDifference * yDifference);
	float combinedRadii = circle1.radius + circle2.radius;

	float overlap = 0.5f * (distance - combinedRadii);

	float xNormal = xDifference / distance;
	float yNormal = yDifference / distance;

	float xTangent = -yNormal;
	float yTangent = xNormal;

	// Velocity along the normal
	// Amount of velocity along each respective normal
	float velocity1AlongNormal = circle1.xVelocity * xNormal + circle1.yVelocity * yNormal;
	float velocity2AlongNormal = circle2.xVelocity * xNormal + circle2.yVelocity * yNormal;

	// Velocity along the tangent
	float velocity1AlongTangent = circle1.xVelocity * xTangent + circle1.yVelocity * yTangent;
	float velocity2AlongTangent = circle2.xVelocity * xTangent + circle2.yVelocity * yTangent;

	// New velocities
	float newVelocity1AlongNormal = velocity2AlongNormal;
	float newVelocity2AlongNormal = velocity1AlongNormal;

	circle1.x += overlap * xNormal;
	circle1.y += overlap * yNormal;

	circle2.x -= overlap * xNormal;
	circle2.y -= overlap * yNormal;

	// We figure out the x and y velocities stored within the velocitiy along the normals
	// to then assign to the circle's x and y velocities to move them accordingly
	circle1.xVelocity = newVelocity1AlongNormal * xNormal + velocity1AlongTangent * xTangent;
	circle1.yVelocity = newVelocity1AlongNormal * yNormal + velocity1AlongTangent * yTangent;

	circle2.xVelocity = newVelocity2AlongNormal * xNormal + velocity2AlongTangent * xTangent;
	circle2.yVelocity = newVelocity2AlongNormal * yNormal + velocity2AlongTangent * yTangent;

	std::cout << "Repelling circles";
}