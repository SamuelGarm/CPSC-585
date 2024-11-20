#pragma once

#include "GLHandles.hpp"
#include <GL/glew.h>
#include <string>

#include <glm/glm.hpp>





class Texture {
public:
	Texture(std::string path, GLint interpolation);

	// Because we're using the TextureHandle to do RAII for the texture for us
	// and our other types are trivial or provide their own RAII
	// we don't have to provide any specialized functions here. Rule of zero
	//
	// https://en.cppreference.com/w/cpp/language/rule_of_three
	// https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md#Rc-zero

	// Public interface
	std::string getPath() const { return path; }
	GLenum getInterpolation() const { return interpolation; }

	// Although uint (i.e. uvec2) might make more sense here, went with int (i.e. ivec2) under
	// the assumption that most students will want to work with ints, not uints, in main.cpp
	glm::ivec2 getDimensions() const { return glm::uvec2(width, height); }

	void bind() { glBindTexture(GL_TEXTURE_2D, textureID); }
	void unbind() { glBindTexture(GL_TEXTURE_2D, textureID); }

	//the texture contains a NO_TEXTURE singleton that can be used wherever a texture is required but not provided by default
	static Texture* getNoTextureTexture();

private:
	TextureHandle textureID;
	std::string path;
	GLint interpolation;
	static Texture* noTexture;


	// Although uint might make more sense here, went with int under the assumption
	// that most students will want to work with ints, not uints, in main.cpp
	int width;
	int height;
};

