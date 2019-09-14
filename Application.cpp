#include <Gl/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

enum ShaderType
{
	Vertex,
	Fragment
};

unsigned int CompileShader(GLenum type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* cSource = source.c_str();
	glShaderSource(id, 1, &cSource, nullptr);
	glCompileShader(id);
	return id;
}



unsigned int CreateShader(const std::string& vertexSource, const std::string& fragmentSource)
{
	unsigned int program = glCreateProgram();
	unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
	unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);

	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}

std::string ParseShader(const std::string& filepath)
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

int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error initializing glew library!" << std::endl;
	}
	else
	{
		std::cout << "Glew initialized successfully!" << std::endl;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;

	float positions[] =
	{
		-0.5f, 0.5f,
		0.0f, -0.5f,
		0.5f, -0.5f
	};

	unsigned int vertexBuffer;
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, positions, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	std::string vertexShaderPath = "Shaders/VertexShader.glsl";
	std::string vertexShader = ParseShader(vertexShaderPath);


	// Pinky triangle!
	std::string fragmentShaderPath = "Shaders/FragmentShader.glsl";
	std::string fragmentShader = ParseShader(fragmentShaderPath);
	unsigned int shader = CreateShader(vertexShader, fragmentShader);
	glUseProgram(shader);

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glDeleteShader(shader);
	glfwTerminate();
	return 0;
}