#include <stdio.h>
#include "libs.h"
#include "Display.h"
#include <stdexcept>

float vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

int main(int argv,char** argc) 
{
	Display display(800, 600, "Hello World");

	//-----START VERTEX SHADER-----


	const char* vertexShaderSource = 
		"#version 330 core\n"
		"layout (location = 1) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\0";
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//-----START FRAGMENT SHADER-----
	const char* fragmentShaderSource =
		"#version 330 core\n"
		"out vec4 FragColor;\n"
		"void main()\n"
		"{\n"
		"FragColor = vec4(1.0f,0.5f,0.2f,1.0f);\n"
		"}\0";

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	//-----END FRAGMENT SHADER-----



	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	GLint success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		GLchar infoLog;
		glGetProgramInfoLog(shaderProgram, 512, NULL, &infoLog);
		printf("%s", infoLog);
		throw std::runtime_error("No se ha podido linkear shaders");
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLuint  VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//El primer parametro de laprimera y la segunda función usan un 1 
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexArrayAttrib(1);
	glUseProgram(shaderProgram);

	while (!display.isClosed()) {
		glClearColor(0.0f, 0.5f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		//Debugging esto se debería convertir en una clase
		display.Update();
	}

	return 0;
}
