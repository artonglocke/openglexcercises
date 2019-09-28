#include "Shader.h"
#include <sstream>
#include <fstream>
#include "Renderer.h"


Shader::Shader(const std::string& filepath)
	: _filepath(filepath), _Id(0)
{
	std::string vertexSource = _parseShader(filepath + "/VertexShader.glsl");
	std::string fragmentSource = _parseShader(filepath + "/FragmentShader.glsl");

	_Id = _createShader(vertexSource, fragmentSource);

}


Shader::~Shader()
{
	glVerify(glDeleteProgram(_Id));
}

void Shader::bind() const
{
	glVerify(glUseProgram(_Id));
}

void Shader::unbind() const
{
	glVerify(glUseProgram(0));
}

void Shader::setUniformLocation1f(std::string name, float value)
{
	glVerify(glUniform1f(_getUniformLocation(name), value));
}

void Shader::setUniformLocation4f(std::string name, float value0, float value1, float value2, float value3)
{
	glVerify(glUniform4f(_getUniformLocation(name), value0, value1, value2, value3));
}

void Shader::setUniformLocation1i(std::string name, int value)
{
	glVerify(glUniform1i(_getUniformLocation(name), value));
}

std::string Shader::_parseShader(const std::string & filepath)
{
	std::ifstream stream(filepath);
	std::string line;
	std::stringstream sourceStream;
	while (std::getline(stream, line))
	{
		sourceStream << line << "\n";
	}

	return sourceStream.str();
}

unsigned int Shader::_compileShader(unsigned int type, const std::string & source)
{
	glVerify(unsigned int id = glCreateShader(type));
	const char* cSource = source.c_str();
	glVerify(glShaderSource(id, 1, &cSource, nullptr));
	glVerify(glCompileShader(id));
	return id;
}

unsigned int Shader::_createShader(const std::string & vertexSource, const std::string & fragmentSource)
{
	glVerify(unsigned int program = glCreateProgram());
	unsigned int vertexShader = _compileShader(GL_VERTEX_SHADER, vertexSource);
	unsigned int fragmentShader = _compileShader(GL_FRAGMENT_SHADER, fragmentSource);

	glVerify(glAttachShader(program, vertexShader));
	glVerify(glAttachShader(program, fragmentShader));
	glVerify(glLinkProgram(program));
	glVerify(glValidateProgram(program));

	glVerify(glDeleteShader(vertexShader));
	glVerify(glDeleteShader(fragmentShader));

	return program;
}

int Shader::_getUniformLocation(const std::string& name)
{
	if (_uniformCache.find(name) != _uniformCache.end())
	{
		return _uniformCache[name];
	}

	glVerify(int uniformLocation = glGetUniformLocation(_Id, name.c_str()));
	if (uniformLocation == -1)
	{
		std::cout << "Error capturing uniform location for " << name << std::endl;
	}
	_uniformCache[name] = uniformLocation;
	return uniformLocation;
}
