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
	-0.5f, -0.5f, 1.0f,  // 왼쪽 아래
	+0.5f, -0.5f, 1.0f,  // 오른쪽 아래
	-0.5f, +0.5f, 1.0f,  // 왼쪽 위     (여기까지 삼각형 1)
	+0.5f, +0.5f, 1.0f,  // 오른쪽 위
	+0.5f, -0.5f, 1.0f,  // 오른쪽 아래
	-0.5f, +0.5f, 1.0f,  // 왼쪽 위     (여기까지 삼각형 2)  => (삼각형 2개로 사각형 생성)
};

int main() {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Window 생성
	GLFWwindow* window = glfwCreateWindow(800, 600, "title", NULL, NULL);
	glfwMakeContextCurrent(window);

	// GLAD 로드 (Window 생성 이후에 실행해야 렉걸리지 않음)
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	// Vertex Shader 생성
	unsigned int vertexShader;
	vertexShader = createAndCompileShader(GL_VERTEX_SHADER, VertexShaderSourceCode);

	// Fragment Shader 생성
	unsigned int fragmentShader;
	fragmentShader = createAndCompileShader(GL_FRAGMENT_SHADER, FragmentShaderSourceCode);

	// Shader Program 생성
	unsigned int shaderProgram = createShaderProgramWithShaders(vertexShader, fragmentShader);

	// VBO 생성 후, 정점 데이터 복사
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// VAO 생성 후, vertex attribute 생성
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*)0);
	glEnableVertexAttribArray(0);

	// Redering Loop
	while(!glfwWindowShouldClose(window)) {

		glClearColor(.5f, .5f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glDrawArrays(GL_TRIANGLES, 1, 3);

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