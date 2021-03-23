#pragma once
#include <vector>
#include "ExternalLibraryHeaders.h"
#include "Helper.h"
#include "Mesh.h"
#include "Camera.h"
#include <string>
#include "ImageLoader.h"

struct Meshes
{
	GLuint vao;
	GLuint numElements{ 0 };
	std::string texturename;
	GLuint texture;
};

class Model
{
public:

	std::vector<Meshes> m_Mesh;
	bool CreateTerrain(int size, std::string texturename, std::string heightmap);
	bool CreateModel(std::string filename, std::string texturename);
	void Render(Meshes mesh, GLuint m_program);

};

