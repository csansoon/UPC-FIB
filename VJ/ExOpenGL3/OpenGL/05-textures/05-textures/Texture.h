#ifndef _TEXTURE_INCLUDE
#define _TEXTURE_INCLUDE


#include <string>
#include <GL/glew.h>


using namespace std;


enum PixelFormat {TEXTURE_PIXEL_FORMAT_RGB, TEXTURE_PIXEL_FORMAT_RGBA};


// The texture class loads images an passes them to OpenGL
// storing the returned id so that it may be applied to any drawn primitives


class Texture
{

public:
	bool loadFromFile(const string &filename, PixelFormat format);
	void use() const;

private:
	GLuint texId;

};


#endif // _TEXTURE_INCLUDE

