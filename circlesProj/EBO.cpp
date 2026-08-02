#include "EBO.h"

EBO::EBO(GLuint* indices, GLsizeiptr size) {
	glGenBuffers(1, &eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);

	// Allocates gpu buffer storage and actually stores the data into the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

EBO::EBO(const std::vector<unsigned int> &indices, GLsizeiptr size) {
	glGenBuffers(1, &eboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);

	// Allocates gpu buffer storage and actually stores the data into the buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
}

// Selects this as the current EBO to be used
void EBO::Bind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
}
// Unselects buffer to not be accidentally overwritten
void EBO::Unbind() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

// Deletes the EBO
void EBO::Delete() {
	glDeleteBuffers(1, &eboID);
}