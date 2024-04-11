#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.h"
// 안쓰면 LINK : warning LNK4098: 'MSVCRT' defaultlib가 다른 라이브러리와 충돌합니다. /NODEFAULTLIB:library를 사용하십시오. 경고 발생
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

float vertice[] = {
	// position			// texture coords
	-0.5, -0.5, 1.0,	0.0f, 0.0f,
	0.5, -0.5, 1.0,		1.0f, 0.0f,
	0, 0.5, 1.0,		1.0f, 1.0f
};

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "hello texture", NULL, NULL);
	glfwMakeContextCurrent(window);

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertice), vertice, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 5, (void*)(sizeof(float) * 3));
	glEnableVertexAttribArray(1);

	Shader shader("4.1.texture.vs", "4.1.texture.fs");

	// Create Texture & Bind
	unsigned int texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	// Texture Image Loading
	int width, height, component_count;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &component_count, 0);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(data);

	while (!glfwWindowShouldClose(window)) {
		glClearColor(0.5, 0.5, 0.5, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindTexture(GL_TEXTURE_2D, texture);
		shader.use();
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
}