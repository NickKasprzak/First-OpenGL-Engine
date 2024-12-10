#pragma once
#include <glad/glad.h>
#include <string>

class Texture
{
public:
	void Generate(int width, int height, int nrComponents, void* data);
	void Dispose();

	void Bind(int textureUnit = -1);
	void Unbind();

	void SetType(std::string type) { _type = type; }

	unsigned int GetID() { return _ID; }
	std::string GetType() { return _type; }
	std::string GetPath() { return _path; }

private:
	unsigned int _ID;
	std::string _type;
	std::string _path;

	int _width;
	int _height;
	GLenum _target;
	GLenum _internalFormat;
	GLenum _format;
	GLenum _sizeType;

	GLenum _wrapMode;
	GLenum _minFilter;
	GLenum _magFilter;
};

/*
* private constructor for friend classes?
* is that how libraries abstract object construction
* through special functions?
* 
* like, say i wanted texture to only be created
* through some global createTexture function. when
* this gets called, some hidden friend resource manager
* class gets an empty texture class from its pool
* allocator and returns it through the function.
* 
* though, thats not really a constructor thing, more
* of an object pool and allocation thing yaya.
* 
* buuuuuut the init function could be private so
* the user cant directly change what ids and stuff
* the texture class contains, its hard set when
* it gets "created" and can only be changed after
* its been flagged to be deleted and is considered
* trashed.
* 
* def a later thing once i figure out how the object
* pools should be organized.
*/