#ifndef TEXTURE_H
#define TEXTURE_H
#include <iostream>

class Texture
{
public:
	Texture(std::string filepath);
	~Texture();

	void bind(unsigned int slot = 0) const;
	void unbind() const;

private:
	unsigned int _Id;
	std::string _filepath;
	unsigned char* _buffer;
	int _width, _height, _bitsPerPixel;
};

#endif // !TEXTURE_H
