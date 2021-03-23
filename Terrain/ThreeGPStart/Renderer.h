#pragma once

#include "ExternalLibraryHeaders.h"

#include "Helper.h"
#include "Mesh.h"
#include "Model.h"
#include "Camera.h"
#include <string>

struct Mesh
{
	GLuint vao;
	GLuint numElements{ 0 };
};


class Renderer
{
private:
	GLuint texture;

	std::vector<Model*> m_Model; // * KD

	// Program object - to host shaders
	GLuint m_program{ 0 };

	// Vertex Array Object to wrap all render settings
	GLuint m_VAO{ 0 };

	// Number of elments to use when rendering
	GLuint m_numElements{ 0 };

	bool m_wireframe{ false };

	bool CreateProgram();
	void CreateModel(std::string filename, std::string texturename);


public:
	Renderer();
	~Renderer();
	void DefineGUI();

	// Create and / or load geometry, this is like 'level load'
	bool InitialiseGeometry();

	// Render the scene
	void Render(const Helpers::Camera& camera, float deltaTime);
};

