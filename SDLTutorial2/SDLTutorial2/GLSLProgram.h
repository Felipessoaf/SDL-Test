#pragma once

#include <string>
#include <GL/glew.h>

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();

	void CompileShaders(const std::string& vertexShaderFilePath, const std::string& fragmentShaderFilePath);
	void LinkShaders();
	void AddAttribute(const std::string& attributeName);

	GLint GetUniformLocation(const std::string uniformName);

	void Use();
	void Unuse();

private:

	int _numAttributes;

	void CompileShader(const std::string& path, GLuint& id);

	GLuint _programID;
	GLuint _vertexShaderID;
	GLuint _fragmentShaderID;
};

