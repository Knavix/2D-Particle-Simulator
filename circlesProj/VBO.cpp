#include "VBO.h"
#include <vector>


VBO::VBO(GLfloat* vertices, GLsizeiptr size) {
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	// Allocates gpu buffer storage and actually stores the data into the buffer
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

VBO::VBO(const std::vector<float> &vertices, GLsizeiptr size) {
	glGenBuffers(1, &vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	// Allocates gpu buffer storage and actually stores the data into the buffer
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
}

// Selects this as the current VVO to be used
void VBO::Bind() {
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
}

// Unselects buffer to not be accidentally overwritten
void VBO::Unbind() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
// Deletes the VBO
void VBO::Delete() {
	glDeleteBuffers(1, &vboID);
}