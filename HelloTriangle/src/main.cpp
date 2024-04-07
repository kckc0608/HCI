#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* pWindow, int width, int height);

int main(int argc, char** argv)
{
	unsigned int VBO;
	unsigned int VAO;

	float vertices[] = {
	-0.5f, -0.5f, 0.0f, // 왼쪽 아래
	 0.5f, -0.5f, 0.0f, // 오른쪽 아래
	 0.0f,  0.5f, 0.0f  // 위
	};

	const char* vertexShaderSourceCode = 
		"#version 330 core \n"
		"layout (location = 0) in vec3 aPos; \n"
		"void main() { \n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
		"} \0";

	const char* fragmentShaderSourceCode =
		"#version 330 core \n"
		"out vec4 FragColor; \n"
		"void main() { \n"
		"	FragColor = vec4(1.0f, 0.5, 0.2f, 1.0f); \n"
		"} \n";

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "practicee", NULL, NULL);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// VBO 생성 & 데이터 소스 연결
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Vertex Shader 생성 및 컴파일
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSourceCode, NULL);
	glCompileShader(vertexShader);

	// Fragment Shader 생성 및 컴파일
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSourceCode, NULL);
	glCompileShader(fragmentShader);

	// Shader Program 생성 및 셰이더 연결
	unsigned int shaderProgram;
	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);

	// VAO 생성 & 속성값 주입
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	glViewport(0, 0, 800, 600);
	while (!glfwWindowShouldClose(window)) {
		glClearColor(.8f, .7f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* pWindow, int width, int height)
{
	//glViewport(0, 0, width, height);
}