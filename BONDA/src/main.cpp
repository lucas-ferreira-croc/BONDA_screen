#include <iostream>>
#include <map>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#define STB_IMAGE_IMPLEMENTATION
#include "vendor/stb_image.h"

#include "shader/shader.h"

void framebuffer_size_callback(GLFWwindow* window, int width, int height);

const int WINDOW_WIDTH = 1280 , WINDOW_HEIGHT = 720;

std::vector < std::string> images = {
	"C:/dev/BONDA/BONDA/src/assets/1.png",
	"C:/dev/BONDA/BONDA/src/assets/2.png",
	"C:/dev/BONDA/BONDA/src/assets/3.png",
	"C:/dev/BONDA/BONDA/src/assets/4.png",
	"C:/dev/BONDA/BONDA/src/assets/5.png",
	"C:/dev/BONDA/BONDA/src/assets/6.png",
	"C:/dev/BONDA/BONDA/src/assets/7.png",
	"C:/dev/BONDA/BONDA/src/assets/8.png",
	"C:/dev/BONDA/BONDA/src/assets/9.png",
	"C:/dev/BONDA/BONDA/src/assets/10.png",
	"C:/dev/BONDA/BONDA/src/assets/11.png",
	"C:/dev/BONDA/BONDA/src/assets/12.png",
	"C:/dev/BONDA/BONDA/src/assets/13.png",
	"C:/dev/BONDA/BONDA/src/assets/14.png",
	"C:/dev/BONDA/BONDA/src/assets/15.png",
	"C:/dev/BONDA/BONDA/src/assets/16.png",
	"C:/dev/BONDA/BONDA/src/assets/17.png"
};

int main(int argc, char** argv)
{

	int music = atoi(argv[1]) - 1;
	if(music < 0 || music > 16)
	{
		std::cout << "escolha uma musica entre 1 e 17" << std::endl;
		return -1;
	}


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
	Shader shader_textures("C:/dev/BONDA/BONDA/src/assets/text_vertex.glsl", "C:/dev/BONDA/BONDA/src/assets/text_fragment.glsl");
	

	
	float vertices_background[] = {
		1.0f,   1.0f,  0.0f,  0.0f, 1.0f, 0.0f,       // top right
		1.0f,  -1.0f,  0.0f,  0.0f, 1.0f, 1.0f,       // bottom right
	   -1.0f,  -1.0f,  0.0f,  1.0f, 0.0f, 1.0f,       // bottom left
	   -1.0f,   1.0f,  0.0f,  1.0f, 0.0f, 0.0f,       // top left 
	};						 

	float vertices_black[] = {
		-0.10f,   0.5f,  0.0f,  0.0f, 0.0f, 0.0f,     // top right
		-0.10f,  -0.75f, 0.0f,  0.0f, 0.0f, 0.0f,     // bottom right
		-0.85f,  -0.75f, 0.0f,  0.0f, 0.0f, 0.0f,     // bottom left
		-0.85f,   0.5f,  0.0f,  0.0f, 0.0f, 0.0f      // top left 
	};

	float BONDA_vertices[] = {

		// positions               //colors              //texture coords
		-0.10f,  -0.55f,  0.0f,    1.0f, 0.0f, 0.0f,     1.0f, 1.0f,       // top right
		-0.10f,  -0.75f,  0.0f,    1.0f, 0.0f, 0.0f,     1.0f, 0.0f,        // bottom right
		-0.50f,  -0.75f,  0.0f,    1.0f, 0.0f, 0.0f,     0.0f, 0.0f,        // bottom left
		-0.50f,  -0.55f,  0.0f,    1.0f, 0.0f, 0.0f,     0.0f, 1.0f,         // top left
	};

	float music_info_vertices[] = {

		 0.90f,   0.5f,  0.0f,     1.0f, 0.0f, 1.0f,      1.0f, 1.0f,    // top right
		 0.90f,  -0.75f, 0.0f,     0.0f, 1.0f, 0.0f,      1.0f, 0.0f,    // bottom right
		 0.1f,  -0.75,  0.0f,     0.0f, 0.0f, 1.0f,      0.0f, 0.0f,     // bottom left
		 0.1f,   0.5f,  0.0f,     1.0f, 1.0f, 0.0f,      0.0f, 1.0f      // top left
	};

	
	unsigned int texture, texture2;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// load and generate the texture
	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("C:/dev/BONDA/BONDA/src/assets/BONDA.png", &width, &height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);


	glGenTextures(1, &texture2);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	std::cout << "argv = " << music << std::endl;
	std::cout << "loading image" << images[music];
	data = stbi_load(images[music].c_str(), &width, &height, &nrChannels, 0);
	if (data)
	{
		// note that the awesomeface.png has transparency and thus an alpha channel, so make sure to tell OpenGL the data type is of GL_RGBA
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture2" << std::endl;
	}
	stbi_image_free(data);

	unsigned int indices[] = {  
	  0, 1, 3, 
	  1, 2, 3, 
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
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	int viewport[4];

	unsigned int vaoImages, vboImages, eboImages;
	glGenVertexArrays(1, &vaoImages);
	glGenBuffers(1, &vboImages);
	glGenBuffers(1, &eboImages);

	glBindVertexArray(vaoImages);
	glBindBuffer(GL_ARRAY_BUFFER, vboImages);
	glBufferData(GL_ARRAY_BUFFER, sizeof(BONDA_vertices), BONDA_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboImages);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	//// TODO: testing 
	unsigned int vao3, vbo3, ebo3;
	glGenVertexArrays(1, &vao3);
	glGenBuffers(1, &vbo3);
	glGenBuffers(1, &ebo3);

	glBindVertexArray(vao3);
	glBindBuffer(GL_ARRAY_BUFFER, vbo3);
	glBufferData(GL_ARRAY_BUFFER, sizeof(music_info_vertices), music_info_vertices, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo3);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);


	
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


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		shader_textures.use();
		shader_textures.setInt("u_bonda", 1);
		glBindTexture(GL_TEXTURE_2D, texture2);
		glBindVertexArray(vao3);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo3);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glDisable(GL_BLEND);
		shader_textures.use();
		shader_textures.setInt("u_bonda", 0);
		shader_textures.setFloat("u_time", glfwGetTime());
		glBindTexture(GL_TEXTURE_2D, texture);
		glBindVertexArray(vaoImages);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboImages);
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