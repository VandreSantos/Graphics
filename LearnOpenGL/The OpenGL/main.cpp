#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shader.h"
#include "Textures.h"
#include "Camera.h"

void resizeCallback(GLFWwindow* window, int width, int height);
void userInputs(GLFWwindow* window);
void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
void cursorCallback(GLFWwindow* window, double xpos, double ypos);

constexpr int width{ 800 };
constexpr int height{ 600 };
float lastX{ width / 2 };
float lastY{ height / 2 };

float lastFrame{ 0.0f };
float deltaTime{};

glm::vec3 lightPos = glm::vec3(1.2f, 1.0f, 2.0f);

Camera ourCamera(glm::vec3(0.0f, 1.0f, 3.0f), -20.0f);

int main()
{
	#pragma region Init
	/*
		DEPOIS DE INICIALIZAR O OPENGL PARA USO, DEFINIMOS ALGUMAS CONFIGURAÇÕES DE INICIALIZAÇÃO, 
		SENDO ELAS A VERSÃO QUE VAMOS USAR DO OPENGL (3.3) E O PERFIL DO OPENGL COMO SENDO CORE 
		(PERFIL QUE REMOVE ALGUMAS FINCIONALIDADES ANTIGAS).
	*/
	#pragma endregion
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Engine", NULL, NULL);
	glfwSetWindowPos(window, 550, 250);
	if (!window)
	{
		std::cout << "FALHA_AO_CRIAR_JANELA!" << "\n";
		glfwTerminate();
		return -1;
	}
	
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, resizeCallback);
	glfwSetScrollCallback(window, scrollCallback);
	glfwSetCursorPosCallback(window, cursorCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "FALHA_AO_INICIALIZAR_GLAD!" << "\n";
		return -1;
	}

	Shader objectShader("C:\\Users\\vandr\\OneDrive\\Documentos\\MeusRepositorios\\Graphics\\LearnOpenGL\\The OpenGL\\Shaders\\ObjectShaderV.txt", "C:\\Users\\vandr\\OneDrive\\Documentos\\MeusRepositorios\\Graphics\\LearnOpenGL\\The OpenGL\\Shaders\\ObjectShaderF.txt");
	Shader lightShader("C:\\Users\\vandr\\OneDrive\\Documentos\\MeusRepositorios\\Graphics\\LearnOpenGL\\The OpenGL\\Shaders\\LightShaderV.txt", "C:\\Users\\vandr\\OneDrive\\Documentos\\MeusRepositorios\\Graphics\\LearnOpenGL\\The OpenGL\\Shaders\\LightShaderF.txt");


	float vertices[] =
	{
		//	 VERTICES					NORMALS
		 0.5f,  0.5f, -0.5f,		0.0f, 0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,		0.0f, 0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,		0.0f, 0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,		0.0f, 0.0f, -1.0f,
									
		 0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,		1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,		1.0f, 0.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,		1.0f, 0.0f, 0.0f,
									
		-0.5f,  0.5f,  0.5f,	   -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,	   -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	   -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,	   -1.0f, 0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,	   -1.0f, 0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,	   -1.0f, 0.0f, 0.0f,
		   							
		 0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,		0.0f, 1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,		0.0f, 1.0f, 0.0f,
		   							
		 0.5f, -0.5f,  0.5f,		0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,		0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,		0.0f, -1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,		0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,		0.0f, -1.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,		0.0f, -1.0f, 0.0f,
		   							
		 0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,		0.0f, 0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,		0.0f, 0.0f, 1.0f
	};

	/*
		╔═╗╔╗  ╦╔═╗╔═╗╔╦╗
		║ ║╠╩╗ ║║╣ ║   ║
		╚═╝╚═╝╚╝╚═╝╚═╝ ╩
	*/

	unsigned int objectVAO{};
	glGenVertexArrays(1, &objectVAO);
	glBindVertexArray(objectVAO);

	unsigned int VBO{};
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/*
		╦  ╦╔═╗╦ ╦╔╦╗
		║  ║║ ╦╠═╣ ║
		╩═╝╩╚═╝╩ ╩ ╩
	*/
	unsigned int lightVAO{};
	glGenVertexArrays(1, &lightVAO);
	glBindVertexArray(lightVAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	/*
		╦  ╔═╗╔═╗╔═╗
		║  ║ ║║ ║╠═╝
		╩═╝╚═╝╚═╝╩
	*/
	while (!glfwWindowShouldClose(window))
	{
		userInputs(window);

		float currentFrame{ static_cast<float>(glfwGetTime())};
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		//	Limpa o buffer de cor, com cinza escuro.
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		/*
			╔═╗╔╗  ╦╔═╗╔═╗╔╦╗
			║ ║╠╩╗ ║║╣ ║   ║
			╚═╝╚═╝╚╝╚═╝╚═╝ ╩
		*/
		objectShader.use();

		//	MODEL MATRIX
		glm::mat4 model{ glm::mat4(1.0f) };
		objectShader.setMat4("u_model", model);

		objectShader.setVec3("u_lightPos", lightPos);
		objectShader.setVec3("u_camPos", ourCamera.cameraPosition);

		objectShader.setVec3("material.ambientColor", glm::vec3(1.0f, 0.5f, 0.31f));
		objectShader.setVec3("material.diffuseColor", glm::vec3(1.0f, 0.5f, 0.31f));
		objectShader.setVec3("material.specularColor", glm::vec3(0.5f, 0.5f, 0.5f));
		objectShader.setFloat("material.shininess", 32.0f);

		glm::vec3 dif = glm::vec3(1.0f, 1.0f, 1.0f);
		objectShader.setVec3("light.ambient", glm::vec3(0.1f, 0.1f, 0.1f));
		objectShader.setVec3("light.diffuse", dif);
		objectShader.setVec3("light.specular", glm::vec3(1.0f, 1.0f, 1.0f));

		//	VIEW MATRIX
		glm::mat4 view{ glm::mat4(1.0f) };
		view = ourCamera.getView();
		objectShader.setMat4("u_view", view);
		//	PROJECTION MATRIX
		glm::mat4 projection{ glm::mat4(1.0f) };
		float fWidth{ static_cast<float>(width) };
		float fHeight{ static_cast<float>(height) };
		projection = glm::perspective(glm::radians(ourCamera.zoom), fWidth / fHeight, 0.1f, 100.0f);
		objectShader.setMat4("u_projection", projection);

		glBindVertexArray(objectVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);

		/*
			╦  ╦╔═╗╦ ╦╔╦╗
			║  ║║ ╦╠═╣ ║
			╩═╝╩╚═╝╩ ╩ ╩
		*/

		//lightPos.x = cos(glfwGetTime()) * 2.0f;
		//lightPos.z = sin(glfwGetTime()) * 2.0f;;

		lightShader.use();
		glBindVertexArray(lightVAO);

		glm::mat4 lModel = glm::mat4(1.0f);
		lModel = glm::translate(lModel, lightPos);
		lModel = glm::scale(lModel, glm::vec3(0.2f));
		lightShader.setMat4("u_model", lModel);
		lightShader.setMat4("u_view", view);
		lightShader.setMat4("u_projection", projection);

		lightShader.setVec3("lightColor", dif);

		glDrawArrays(GL_TRIANGLES, 0, 36);

		//	Procedimentos da janela
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

/*
	╔═╗╦ ╦╔╗╔╔═╗╔═╗╔═╗╔═╗
	╠╣ ║ ║║║║║  ║ ║║╣ ╚═╗
	╚  ╚═╝╝╚╝╚═╝╚═╝╚═╝╚═╝
*/
void resizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	glfwSwapBuffers(window);
}

void userInputs(GLFWwindow* window)
{
	ourCamera.cameraSpeed = 7.5f;
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		ourCamera.setMovement(FORWARD, deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		ourCamera.setMovement(BACKWARD, deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		ourCamera.setMovement(RIGHT, deltaTime);
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		ourCamera.setMovement(LEFT, deltaTime);
	}
}

void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	float fyoffset{ static_cast<float>(yoffset) };
	ourCamera.setFov(fyoffset);
}

#pragma region cursor
/*
	A função abaixo tem como objetivo a definição das variaveis offset, que consiste na diferença
	da posição inical do mouse para a posição final no intervalo de um quadro, que posteriormente,
	se multiplicarmos por um fator sensibilidade, podemos almentar a velocidade da movimentação da camera.
*/
#pragma endregion
bool firstMouse = true;
void cursorCallback(GLFWwindow* window, double xpos, double ypos)
{
	float xPos{ static_cast<float>(xpos) };
	float yPos{ static_cast<float>(ypos) };

	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;

		firstMouse = false;
	}

	float xoffset{ xPos - lastX };
	float yoffset{ lastY - yPos };
	lastX = xPos;
	lastY = yPos;

	ourCamera.setDirection(xoffset, yoffset, true);
}
