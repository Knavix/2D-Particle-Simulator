#include <iostream>
#include <vector>
#include <cmath>


/*
int main() {
	// Dynamic storage for vertex information
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	// Number of triangles
	int n = 6;
	float pi = 3.14159265f;
	float radius = 0.5f;
	// Arc distance between each point
	float deltaTheta = 2.0f * pi / n;

	// Generating outer ring points
	for (int i = 0; i < n; i++) {
		float angle = i * deltaTheta;

		float x = radius * cosf(angle);
		float y = radius * sinf(angle);
		vertices.push_back(x);
		vertices.push_back(y);
	}
	
	// Center point
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	int centerIndex = n;

	//Triangle fan indices
	for (int i = 0; i < n; i++) {
		int next = (i + 1) % n;
		
		indices.push_back(centerIndex);
		indices.push_back(i);
		indices.push_back(next);
	}

	return 0;
}
*/