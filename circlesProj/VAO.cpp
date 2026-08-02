#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &vaoID);
}

void VAO::LinkVBO(VBO VBO, GLuint layout) {
	VBO.Bind();
	glVertexAttribPointer(layout, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(layout);
	VBO.Unbind();
}

// Selects this as the current VAO to be used
void VAO::Bind() {
	glBindVertexArray(vaoID);
}
// Unselects VAO to not be accidentally overwritten
void VAO::Unbind() {
	glBindVertexArray(0);
}
// Deletes the VAO
void VAO::Delete() {
	glDeleteVertexArrays(1, &vaoID);
}