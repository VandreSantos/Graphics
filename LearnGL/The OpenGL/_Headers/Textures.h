#ifndef TEXTURES_H
#define TEXTURES_H

#include <iostream>
#include <stb_image.h>
#include <glad/glad.h>

class Textures
{
private:
	int tex1Width{};
	int tex1Height{};
	int tex1Channels{};

	int tex2Width{};
	int tex2Height{};
	int tex2Channels{};
public:

	/*
		▀█▀ █▀▀ ▀▄▀ ▀█▀ █░█ █▀█ █▀▀  █▀█ █▀▀ █▄▄
		░█░ ██▄ █░█ ░█░ █▄█ █▀▄ ██▄  █▀▄ █▄█ █▄█
	*/
	void genTextureRGB(unsigned int& textureNameRGB, const char* fileNameRGB)
	{
		glGenTextures(1, &textureNameRGB);
		glBindTexture(GL_TEXTURE_2D, textureNameRGB);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_set_flip_vertically_on_load(true);
		unsigned char* imgData1 = stbi_load(fileNameRGB, &tex1Width, &tex1Height, &tex1Channels, 0);
		if (imgData1)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex1Width, tex1Height, 0, GL_RGB, GL_UNSIGNED_BYTE, imgData1);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "ERRO::FALHA_AO_CARREGAR_IMAGEM\n";
		}
		stbi_image_free(imgData1);
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	/*
		▀█▀ █▀▀ ▀▄▀ ▀█▀ █░█ █▀█ █▀▀  █▀█ █▀▀ █▄▄ ▄▀█
		░█░ ██▄ █░█ ░█░ █▄█ █▀▄ ██▄  █▀▄ █▄█ █▄█ █▀█
	*/
	void genTextureRGBA(unsigned int& textureNameRGBA, const char* fileNameRGBA)
	{
		glGenTextures(1, &textureNameRGBA);
		glBindTexture(GL_TEXTURE_2D, textureNameRGBA);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		stbi_set_flip_vertically_on_load(true);
		unsigned char* imgData2 = stbi_load(fileNameRGBA, &tex2Width, &tex2Height, &tex2Channels, 0);
		if (imgData2)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex2Width, tex2Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData2);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "ERRO::FALHA_AO_CARREGAR_IMAGEM\n";
		}
		stbi_image_free(imgData2);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};

#endif
