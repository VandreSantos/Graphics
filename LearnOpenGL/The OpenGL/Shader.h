#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Shader
{
private:
	std::string vString{};
	std::string fString{};
	std::ifstream vShader{};
	std::ifstream fShader{};
public:
	unsigned int ID{};
	Shader(const char* vertexPath, const char* fragmentPath)
	{
		vShader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShader.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			vShader.open(vertexPath);
			fShader.open(fragmentPath);
			std::stringstream vShaderStream{};
			std::stringstream fShaderStream{};
			vShaderStream << vShader.rdbuf();
			fShaderStream << fShader.rdbuf();
			vShader.close();
			fShader.close();
			vString = vShaderStream.str();	//	Armazena o Vertex Shader como string.
			fString = fShaderStream.str();	//	Armazena o Fragment Shader como string.
		}
		catch (std::ifstream::failure e)
		{
			std::cout << "ERRO_AO_CARREGAR_ARQUIVO!";
		}
		const char* vertexCode = vString.c_str();	//	Armazena o Vertex Shader como const char*
		const char* fragmentCode = fString.c_str(); //	Armazena o Fragment Shader como const char*

		char infoLog[512];
		int success{};

		/*
			╦  ╦╔═╗╦═╗╔╦╗╔═╗═╗ ╦
			╚╗╔╝║╣ ╠╦╝ ║ ║╣ ╔╩╦╝
			 ╚╝ ╚═╝╩╚═ ╩ ╚═╝╩ ╚═
		*/
		#pragma region vertex
		/*
			//	Abaixo, criamos e compilamos o Vertex Shader com o arquivo carregado que foi passado 
			no construtor, agora o nosso arquivo de texto vinculado sera interpretado como o Shader para a 
			renderização dos objetos. 
		*/
		#pragma endregion
		unsigned int vertex{};
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vertexCode, NULL);
		glCompileShader(vertex);
		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "VERTEX::SHADER::ERRO_AO_COMPILAR" << infoLog << "\n";
		}
		/*
			╔═╗╦═╗╔═╗╔═╗╔╦╗╔═╗╔╗╔╔╦╗
			╠╣ ╠╦╝╠═╣║ ╦║║║║╣ ║║║ ║ 
			╚  ╩╚═╩ ╩╚═╝╩ ╩╚═╝╝╚╝ ╩
		*/
		#pragma region vertex
			/*
				//	Abaixo, criamos e compilamos o Fragment Shader com o arquivo carregado que foi passado
				no construtor, agora o nosso arquivo de texto vinculado sera interpretado como o Shader para a
				renderização dos objetos.
			*/
		#pragma endregion
		unsigned int fragment{};
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fragmentCode, NULL);
		glCompileShader(fragment);
		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(fragment, 512, NULL, infoLog);
			std::cout << "FRAGMENT::SHADER::ERRO_AO_COMPILAR" << infoLog << "\n";
		}
		/*
			╔═╗╦═╗╔═╗╔═╗╦═╗╔═╗╔╦╗
			╠═╝╠╦╝║ ║║ ╦╠╦╝╠═╣║║║
			╩  ╩╚═╚═╝╚═╝╩╚═╩ ╩╩ ╩
		*/
		#pragma region program
		/*
			//	Abaixo, criamos o nosso Shader Program e vinculamos tanto o Vertex quanto o 
			Fragment Shader nele, qualquer chamada sequencial para ID, fará o uso dos shaders que
			foram passados no construtor, note que os shaders foram deletatos pois agora estão armazenados no programa.
		*/
		#pragma endregion
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		if (!success)
		{
			glGetShaderInfoLog(ID, 512, NULL, infoLog);
			std::cout << "SHADER::PROGRAM::FALHA_AO_LINKAR" << infoLog << "\n";
		}
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	void use()
	{
		glUseProgram(ID);
	}

	void setBool(const char* name, bool value)
	{
		glUniform1i(glGetUniformLocation(ID, name), static_cast<int>(value));
	}
	void setInt(const char* name, int value)
	{
		glUniform1i(glGetUniformLocation(ID, name), value);
	}
	void setFloat(const char* name, float value)
	{
		glUniform1f(glGetUniformLocation(ID, name), value);
	}
	void setMat4(const char* name, glm::mat4 value)
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, &value[0][0]);
	}
	void setVec3(const char* name, glm::vec3 value)
	{
		glUniform3f(glGetUniformLocation(ID, name), value.x, value.y, value.z);
	}
};
#endif