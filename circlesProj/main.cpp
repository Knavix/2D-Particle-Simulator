#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "shaderClass.h"
#include <vector>
#include <cmath>
#include "VBO.h"
#include "EBO.h"
#include "VAO.h"
#include "Circle.h"
#include "Collision.h"




int main() {
	glfwInit();

	// Set OpenGL version to 3.3 and use the core profile
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creating window
	GLFWwindow* window = glfwCreateWindow(800, 800, "2D Particle Simulator", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Dynamic storage for vertex information
	std::vector<float> vertices;
	std::vector<unsigned int> indices;

	// n = Number of triangles
	int n = 50;
	float pi = 3.14159265f;
	float radius = 1.0f;

	// ----Circle Vector---
	std::vector<Circle> circles;
	// ------------------------ Number of Circles --------------------//
	float circleCount = 800;

	int columns = static_cast<int>(std::ceil(std::sqrt(circleCount)));
	float spacing = 1.6f / columns;

	// --- Multi-Circle Loop ---
	
	for (int i = 0; i < circleCount; i++) {
		Circle circle;
		int column = i % columns;
		int row = i / columns;

		float velocityRange = -0.7f;
		float xRandom = velocityRange + static_cast<float>(rand()) / RAND_MAX;
		float yRandom = velocityRange + static_cast<float>(rand()) / RAND_MAX;

		float minRadius = 0.01f;
		float maxRadius = 0.03f;
		float randomValueRadius = static_cast<float>(rand()) / RAND_MAX;
		float randomRadius = minRadius + randomValueRadius * (maxRadius - minRadius);

		circle.setRadius(randomRadius);
		circle.mass = randomRadius * randomRadius;
		circle.x = -0.8f + column * spacing;
		circle.y = -0.8 + row * spacing;
		circle.xVelocity = xRandom;
		circle.yVelocity = yRandom;

		circles.push_back(circle);
	}

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

	// Selecting this as the current window we're working with
	glfwMakeContextCurrent(window);
	// Loading glad to allow us to use opengl functions
	gladLoadGL();
	glViewport(0, 0, 800, 800);

	// Creates a shader object that links and compiles given shader code
	Shader shaderOne("shader.vs", "shader.frag");

	// Generates Vertex Array object and binds it
	VAO VAO1;
	VAO1.Bind();
	// Generates VBO and EBO and stores the vertices and indices respectively
	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

	// Links the VAO to the VBO
	VAO1.LinkVBO(VBO1, 0);

	//Unbinds all to not accidently overwrite
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	// ------------Circle Offset -------------

	float previousTime = glfwGetTime();
	float deltaTime = 0.0f;


	// -------------------------  MAIN LOOP  --------------------------//

	while (!glfwWindowShouldClose(window)) {
		// The color of the background
		glClearColor(158 / 255.0f, 185 / 255.0f, 240 / 255.0f, 1.0f);
		// Clears back buffer and replaces with previously established color
		glClear(GL_COLOR_BUFFER_BIT);
		// Selects the shaderprogram
		shaderOne.use();

		float currentTime = glfwGetTime();
		deltaTime = currentTime - previousTime;
		previousTime = currentTime;


		for (Circle& circle : circles) {
			circle.x += circle.xVelocity * deltaTime;
			circle.y += circle.yVelocity * deltaTime;

			circle.handleWallCollisions(-1.0f, 1.0f, 1.0f, -1.0f);
		}

		int collisionNumb = 0;
		collisionNumb++;

		for (int i = 0; i < circles.size(); i++) {
			for (int j = i + 1; j < circles.size(); j++) {
				if (areCirclesColliding(circles[i], circles[j])) {
					repelCircles(circles[i], circles[j]);
				}
			}
		}

		collisionNumb = 5;
		// Selects the specific VAO containing the config for reading vertex data
		VAO1.Bind();

		for (Circle& circle : circles) {
			shaderOne.setVec2("uOffset", circle.x, circle.y);
			shaderOne.setFloat("uScale", circle.radius);
			glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		}

		// Swaps the back and front buffers for the next frame to be shown
		glfwSwapBuffers(window);
		// Handles glfw events
		glfwPollEvents();
	}

	// Cleaning objects no longer needed
	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderOne.Delete();
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}