#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader_s.h"
#include <iostream>

float vertex_data[] = {
	-0.5, -0.5, 1.0, 0.2, 0.2, 0.2, // 왼쪽 아래
	 0.5, -0.5, 1.0, 0.3, 0.3, 0.3, // 오른쪽 아래
	-0.5,  0.5, 1.0, 0.4, 0.4, 0.4, // 왼쪽 위
	 0.5,  0.5, 1.0, 0.5, 0.5, 0.5, // 오른쪽 위
};

unsigned int index_data[] = {
	0, 1, 2,
	1, 2, 3
};

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Colored Rectangle", NULL, NULL);
	glfwMakeContextCurrent(window);

	// glad load
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "GLAD 로드 중 에러 발생\n";
		return -1;
	}

	// Shader 생성
	Shader shader("vertex_shader.vs", "fragment_shader.fs");

	// VAO, VBO, EBO
	unsigned int VAO, VBO, EBO;

	// VAO 생성 & Context에 바인딩
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO 생성, VAO에 바인딩, 데이터 소스 연결
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

	// EBO 생성, VAO에 바인딩, EBO 소스 연결
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_data), index_data, GL_STATIC_DRAW);

	// Vertex Attribute 데이터 연결
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0); // 위치
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float)*3)); // 색상
	//glEnableVertexAttribArray(1);

	// Uniform 변수 생성 & 색상 초기값 세팅
	int colorUniformLoc = glGetUniformLocation(shader.ID, "uniformColor");
	glUniform3f(colorUniformLoc, 0.0, 0.0, 0.0);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.5, 0.5, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		double time = glfwGetTime();
		float redColor = abs(sin(time));
		glUniform3f(colorUniformLoc, redColor, 0.0, 0.0); // 렌더링 루프에서 uniform 변수값을 지정해야 함.
		
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		/*glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 1, 3);*/

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}