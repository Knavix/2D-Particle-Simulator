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
	GLFWwindow* window = glfwCreateWindow(800, 800, "My Window", NULL, NULL);
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
	float radius = 0.3f;

	// -----Circle -------
	
	Circle circle1;

	circle1.x = -0.50f;
	circle1.y = 0.0f;
	circle1.setRadius(radius);
	circle1.xVelocity = 0.7f;
	circle1.yVelocity = 0.3f;

	Circle circle2;
	circle2.x = 0.5f;
	circle2.y = 0.0f;
	circle2.setRadius(radius);
	circle2.xVelocity = -0.4f;
	circle2.yVelocity = -0.8f;

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



	// Window loop happening every frame
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

		circle1.x += circle1.xVelocity * deltaTime;
		circle1.y += circle1.yVelocity * deltaTime;

		circle2.x += circle2.xVelocity * deltaTime;
		circle2.y += circle2.yVelocity * deltaTime;

		circle1.handleWallCollisions(-1.0f, 1.0f, 1.0f, -1.0f);
		circle2.handleWallCollisions(-1.0f, 1.0f, 1.0f, -1.0f);
		int collisionNumb = 0;
		collisionNumb++;
		if (areCirclesColliding(circle1, circle2)) {
			repelCircles(circle1, circle2);
			std::cout << "Collision! " << collisionNumb++<<"\n";
		}
		collisionNumb = 5;
		shaderOne.setVec2("uOffset", circle1.x, circle1.y);
		// Selects the specific VAO containing the config for reading vertex data
		VAO1.Bind();
		// The big function that actually "draws" from the data ha
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

		shaderOne.setVec2("uOffset", circle2.x, circle2.y);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
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