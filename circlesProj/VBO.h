#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <vector>
#include <glad/glad.h>

class VBO {
	public:
		GLuint vboID;
		VBO(GLfloat* vertices, GLsizeiptr size);
		VBO(const std::vector<float> &vertices, GLsizeiptr size);

		void Bind();
		void Unbind();
		void Delete();
};

#endif