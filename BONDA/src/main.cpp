#include <iostream>>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "shader/shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const int WINDOW_WIDTH = 1280 , WINDOW_HEIGHT = 720;
int main(int argc, char** argv)
{
	//glfw initialization
	if (!glfwInit()) 
	{
		std::cout << "failed initializing GLFW" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);


	// window and context creation
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "BONDA", NULL, NULL);
	if(!window)
	{
		std::cout << "Failed creating GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;
	
	if(glewInit() != GLEW_OK)
	{
		std::cout << "GLEW initialization failed" << std::endl;
		glfwDestroyWindow(window);
		glfwTerminate();
		return -1;
	}

	Shader shader_rainbow("C:/dev/BONDA/BONDA/src/assets/vertex.glsl", "C:/dev/BONDA/BONDA/src/assets/rainbow_fragment.glsl");
	Shader shader_black("C:/dev/BONDA/BONDA/src/assets/vertex.glsl", "C:/dev/BONDA/BONDA/src/assets/black_fragment.glsl");

	float vertices_background[] = {
		1.0f,   1.0f,  0.0f,  0.0f, 1.0f, 0.0f,   // top right
		1.0f,  -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,   // bottom right
	   -1.0f,  -1.0f,  0.0f,  1.0f, 0.0f, 1.0f,   // bottom left
	   -1.0f,   1.0f,  0.0f,  1.0f, 0.0f, 0.0f,   // top left 
	};						 

	float vertices_black[] = {
		-0.10f,   0.5f,  0.0f,  0.0f, 0.0f, 0.0f,     // top right
		-0.10f,  -0.75f, 0.0f,  0.0f, 0.0f, 0.0f,     // bottom right
		-0.85f,  -0.75f, 0.0f,  0.0f, 0.0f, 0.0f,     // bottom left
		-0.85f,   0.5f,  0.0f,  0.0f, 0.0f, 0.0f     // top left 
	};

	unsigned int indices[] = {  
	  0, 1, 3,   // primeiro triângulo (do primeiro quadrado)
	  1, 2, 3,   // segundo triângulo (do primeiro quadrado)
	};

	unsigned int ebo;
	glGenBuffers(1, &ebo);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	unsigned int vao, vbo;
	
	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_background), vertices_background, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


	unsigned int vao2, vbo2, ebo2;
	glGenVertexArrays(1, &vao2);
	glGenBuffers(1, &vbo2);
	glGenBuffers(1, &ebo2);

	glBindVertexArray(vao2);
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_black), vertices_black, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(vertices_black), indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	int viewport[4];
	
	while(!glfwWindowShouldClose(window))
	{
		glGetIntegerv(GL_VIEWPORT, viewport);

		int width = viewport[2];
		int height = viewport[3];

		glfwPollEvents();

		glClearColor(0.5f, 0.0f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		
		shader_rainbow.use();
		shader_rainbow.setFloat("u_time", (float)glfwGetTime());
		glBindVertexArray(vao);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		shader_black.use();
		glBindVertexArray(vao2);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		glfwSwapBuffers(window);
	}
	
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);

	
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}