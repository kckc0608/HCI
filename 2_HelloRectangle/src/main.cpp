#include <glad/glad.h>
#include <GLFW/glfw3.h>

unsigned int createAndCompileShader(GLenum shaderEnum, const char* shaderSourceCode);
unsigned int createShaderProgramWithShaders(unsigned int vertexShader, unsigned int fragmentShader);

const char* VertexShaderSourceCode =
	"#version 330 core \n"
	"layout(location = 0) in vec3 aPos; \n"
	"void main() { \n"
	"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
	"} \n";

const char* FragmentShaderSourceCode =
"#version 330 core \n"
"out vec4 FragColor; \n"
"void main() { \n"
"	FragColor = vec4(0.5f, 0.5f, 0.5f, 1.0f); \n"
"} \n";

float vertices[] = {
	-0.5f, -0.5f, 1.0f,  // ���� �Ʒ�
	+0.5f, -0.5f, 1.0f,  // ������ �Ʒ�
	-0.5f, +0.5f, 1.0f,  // ���� ��     (������� �ﰢ�� 1)
	+0.5f, +0.5f, 1.0f   // ������ ��
	//+0.5f, -0.5f, 1.0f,  // ������ �Ʒ�
	//-0.5f, +0.5f, 1.0f,  // ���� ��     (������� �ﰢ�� 2)  => (�ﰢ�� 2���� �簢�� ����)
};

int indices[] = {
	0, 1, 2,
	1, 2, 3
};

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window ����
	GLFWwindow* window = glfwCreateWindow(800, 600, "title", NULL, NULL);
	glfwMakeContextCurrent(window);

	// GLAD �ε� (Window ���� ���Ŀ� �����ؾ� ���ɸ��� ����)
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// Vertex Shader ����
	unsigned int vertexShader;
	vertexShader = createAndCompileShader(GL_VERTEX_SHADER, VertexShaderSourceCode);

	// Fragment Shader ����
	unsigned int fragmentShader;
	fragmentShader = createAndCompileShader(GL_FRAGMENT_SHADER, FragmentShaderSourceCode);

	// Shader Program ����
	unsigned int shaderProgram = createShaderProgramWithShaders(vertexShader, fragmentShader);

	// VAO ���� (VBO, EBO�� �� VAO�� ���ε� �ǹǷ� ���� �����ؾ� ��. �� �׷��� �ﰢ���� �ȱ׷���!)
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	// VBO ���� ��, ���� ������ ����
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// ���� Attribute�� �����ϰ�, VAO�� �Ҵ�
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	// EBO ���� ��, �ε��� ������ ����
	unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Redering Loop
	while(!glfwWindowShouldClose(window)) {

		glClearColor(.5f, .5f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		/*glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 1, 3);*/
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glfwTerminate();
}

unsigned int createAndCompileShader(GLenum shaderEnum, const char* shaderSourceCode) {
	unsigned int shader = glCreateShader(shaderEnum);
	glShaderSource(shader, 1, &shaderSourceCode, NULL);
	glCompileShader(shader);
	return shader;
}

unsigned int createShaderProgramWithShaders(unsigned int vertexShader, unsigned int fragmentShader) {
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	return shaderProgram;
}