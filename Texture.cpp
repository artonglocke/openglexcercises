#include "Texture.h"
#include "stb_image.h"
#include "Renderer.h"

Texture::Texture(std::string filepath)
	: _Id(0), _filepath(filepath), _buffer(nullptr), 
	_width(0), _height(0), _bitsPerPixel(0)
{
	stbi_set_flip_vertically_on_load(1);
	_buffer = stbi_load(_filepath.c_str(), &_width, &_height, &_bitsPerPixel, 4);
	glVerify(glGenTextures(1, &_Id));
	glVerify(glBindTexture(GL_TEXTURE_2D, _Id));

	glVerify(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	glVerify(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	glVerify(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	glVerify(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	// Texture load
	glVerify(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, _width, _height, 0, GL_RGBA, GL_UNSIGNED_BYTE, _buffer));
	glVerify(glBindTexture(GL_TEXTURE_2D, 0));

	if (_buffer)
	{
		stbi_image_free(_buffer);
	}
}

Texture::~Texture()
{
	glVerify(glDeleteTextures(GL_TEXTURE_2D, &_Id));
}

void Texture::bind(unsigned int slot) const
{
	glVerify(glActiveTexture(GL_TEXTURE0 + slot));
	glVerify(glBindTexture(GL_TEXTURE_2D, _Id));
}

void Texture::unbind() const
{
	glVerify(glBindTexture(GL_TEXTURE_2D, 0));
}
