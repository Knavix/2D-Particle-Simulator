#ifndef EBO_CLASS_H
#define EBO_CLASS_H

#include <glad/glad.h>
#include <vector>

class EBO {
public:
	GLuint eboID;
	EBO(GLuint* indices, GLsizeiptr size);
	EBO(const std::vector<unsigned int> &indices, GLsizeiptr size);

	void Bind();
	void Unbind();
	void Delete();
};

#endif
