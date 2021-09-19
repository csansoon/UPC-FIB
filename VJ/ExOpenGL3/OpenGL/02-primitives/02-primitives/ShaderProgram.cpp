#include "ShaderProgram.h"


ShaderProgram::ShaderProgram()
{
	programId = 0;
	linked = false;
}


void ShaderProgram::init()
{
	programId = glCreateProgram();
}

void ShaderProgram::addShader(const Shader &shader)
{
	glAttachShader(programId, shader.getId());
}

void ShaderProgram::bindFragmentOutput(const string &outputName)
{
	glBindAttribLocation(programId, 0, outputName.c_str());
}

GLint ShaderProgram::bindVertexAttribute(const string &attribName, GLint size)
{
	GLint attribPos;

	attribPos = glGetAttribLocation(programId, attribName.c_str());
	glVertexAttribPointer(attribPos, size, GL_FLOAT, GL_FALSE, 0, 0);

	return attribPos;
}

void ShaderProgram::link()
{
	GLint status;
	char buffer[512];

	glLinkProgram(programId);
	glGetProgramiv(programId, GL_LINK_STATUS, &status);
	linked = (status == GL_TRUE);
	glGetProgramInfoLog(programId, 512, NULL, buffer);
	errorLog.assign(buffer);
}

void ShaderProgram::free()
{
	glDeleteProgram(programId);
}

void ShaderProgram::use()
{
	glUseProgram(programId);
}

bool ShaderProgram::isLinked()
{
	return linked;
}

const string &ShaderProgram::log() const
{
	return errorLog;
}

