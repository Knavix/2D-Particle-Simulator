#ifndef SHADER_CLASS_H
#define	SHADER_CLASS_H

#include <glad/glad.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader {
public:
	unsigned programID;

	Shader(const char* vertexPath, const char* fragmentPath);

	void use();
	void Delete();
	void setBool(const std::string &name, bool value) const;
	void setInt(const std::string &name, int value) const;
	void setFloat(const std::string& name, float value) const;
};

#endif