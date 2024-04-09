#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader_s.h"
#include <iostream>

float vertex_data[] = {
	-0.5, -0.5, 1.0, 0.2, 0.2, 0.2, // ���� �Ʒ�
	 0.5, -0.5, 1.0, 0.3, 0.3, 0.3, // ������ �Ʒ�
	-0.5,  0.5, 1.0, 0.4, 0.4, 0.4, // ���� ��
	 0.5,  0.5, 1.0, 0.5, 0.5, 0.5, // ������ ��
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
		std::cout << "GLAD �ε� �� ���� �߻�\n";
		return -1;
	}

	// Shader ����
	Shader shader("vertex_shader.vs", "fragment_shader.fs");

	// VAO, VBO, EBO
	unsigned int VAO, VBO, EBO;

	// VAO ���� & Context�� ���ε�
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO ����, VAO�� ���ε�, ������ �ҽ� ����
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_data), vertex_data, GL_STATIC_DRAW);

	// EBO ����, VAO�� ���ε�, EBO �ҽ� ����
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index_data), index_data, GL_STATIC_DRAW);

	// Vertex Attribute ������ ����
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)0); // ��ġ
	glEnableVertexAttribArray(0);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (void*)(sizeof(float)*3)); // ����
	//glEnableVertexAttribArray(1);

	// Uniform ���� ���� & ���� �ʱⰪ ����
	int colorUniformLoc = glGetUniformLocation(shader.ID, "uniformColor");
	glUniform3f(colorUniformLoc, 0.0, 0.0, 0.0);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.5, 0.5, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		double time = glfwGetTime();
		float redColor = abs(sin(time));
		glUniform3f(colorUniformLoc, redColor, 0.0, 0.0); // ������ �������� uniform �������� �����ؾ� ��.
		
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