#include "Model.h"

bool Model::CreateTerrain(int size, std::string texturename, std::string heightmap)
{
	Meshes newMesh;

	int Cellsx{ 128 };
	int Cellsz{ 128 };

	int Vertsx = Cellsx + 1;
	int Vertsz = Cellsz + 1;

	int Polysx = Cellsx * 2;
	int Polysz = Cellsz;

	float CellSizex = size / (float)Cellsx;
	float CellSizez = size / (float)Cellsz;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> UV;
	std::vector<GLuint> elements;

	glm::vec3 startPos{ -size / 2,0,size / 2 };

	float tiles{ 10.0f };

	Helpers::ImageLoader map;
	if (!map.Load(heightmap))
	{
		std::cout << "ERROR NO HEIGHT MAP" << std::endl;
		return false;
	}
	unsigned char* texels = (unsigned char*)map.GetData();


	for (int z = 0; z < Vertsz; z++)
	{
		for (int x = 0; x < Vertsx; x++)
		{
			glm::vec3 pos{ startPos };

			pos.x += CellSizex * x;
			pos.z -= CellSizez * z;
			//pos.y = rand() % 100;

			float u = (float)x / (Vertsx - 1);
			float v = (float)z / (Vertsz - 1);

			int heightx = u * (map.Width() - 1);
			int heighty = v * (map.Height() - 1);

			int offset = (heightx + heighty * map.Width()) * 4;
			pos.y = texels[offset];

			u *= tiles; v *= tiles;

			UV.push_back(glm::vec2(u, v));
			vertices.push_back(pos);
		}
	}

	for (int z = 0; z < Cellsz; z++)
	{
		for (int x = 0; x < Cellsx; x++)
		{
			//bottom corner of square
			GLuint startVertex = z * Vertsx + x;
			//bottom triangle
			elements.push_back(startVertex);
			elements.push_back(startVertex + 1);
			elements.push_back(startVertex + 1 + Vertsx);
			//top triangle
			elements.push_back(startVertex);
			elements.push_back(startVertex + 1 + Vertsx);
			elements.push_back(startVertex + Vertsx);
		}
	}

	std::vector < glm::vec3>normals(vertices.size());
	std::fill(normals.begin(), normals.end(), glm::vec3(0, 0, 0));

	for (size_t index = 0; index < elements.size(); index += 3)
	{
		int index1 = elements[index];
		int index2 = elements[index + 1];
		int index3 = elements[index + 2];

		glm::vec3 vertice1 = vertices[index1];
		glm::vec3 vertice2 = vertices[index2];
		glm::vec3 vertice3 = vertices[index3];

		glm::vec3 edge1 = vertice2 - vertice1;
		glm::vec3 edge2 = vertice3 - vertice1;

		glm::vec3 normal = glm::normalize(glm::cross(edge1, edge2));

		normals[index1] += normal;
		normals[index2] += normal;
		normals[index3] += normal;
	}
	for (glm::vec3& n : normals)
	{
		n = glm::normalize(n);
	}

	newMesh.numElements = elements.size();
	Helpers::CheckForGLError();
	GLuint vertsVBO;
	glGenBuffers(1, &vertsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, vertsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

	GLuint telementVBO;
	glGenBuffers(1, &telementVBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, telementVBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * elements.size(), elements.data(), GL_STATIC_DRAW);

	GLuint normalsVBO;
	glGenBuffers(1, &normalsVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * normals.size(), normals.data(), GL_STATIC_DRAW);

	GLuint TextureVBO;
	glGenBuffers(1, &TextureVBO);
	glBindBuffer(GL_ARRAY_BUFFER, TextureVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * UV.size(), UV.data(), GL_STATIC_DRAW);

	glGenVertexArrays(1, &newMesh.vao);
	glBindVertexArray(newMesh.vao); 
	Helpers::CheckForGLError();
	Helpers::ImageLoader iloader;
	Helpers::CheckForGLError();

	if (iloader.Load(texturename))
	{
		glGenTextures(1, &newMesh.texture);
		glBindTexture(GL_TEXTURE_2D, newMesh.texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iloader.Width(), iloader.Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, iloader.GetData());
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "ERROR NO TEXTURE" << std::endl;
		return false;
	}

	Helpers::CheckForGLError();
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, telementVBO);
	Helpers::CheckForGLError();
	glBindBuffer(GL_ARRAY_BUFFER, vertsVBO);

	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, vertsVBO);
	glVertexAttribPointer(
		0,                  // attribute 0
		3,                  // size in components of each item in the stream e.g. a position has 3 components x,y and z
		GL_FLOAT,           // type of the item
		GL_FALSE,           // normalized or not (advanced)
		0,                  // stride (advanced)
		(void*)0            // array buffer offset (advanced)
	);
	Helpers::CheckForGLError();
	glBindBuffer(GL_ARRAY_BUFFER, normalsVBO);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,                  // attribute 0
		3,                  // size in components of each item in the stream e.g. a position has 3 components x,y and z
		GL_FLOAT,           // type of the item
		GL_FALSE,           // normalized or not (advanced)
		0,                  // stride (advanced)
		(void*)0            // array buffer offset (advanced)
	);
	Helpers::CheckForGLError();
	glBindBuffer(GL_ARRAY_BUFFER, TextureVBO);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,                  // attribute 0
		2,                  // size in components of each item in the stream e.g. a position has 3 components x,y and z
		GL_FLOAT,           // type of the item
		GL_FALSE,           // normalized or not (advanced)
		0,                  // stride (advanced)
		(void*)0            // array buffer offset (advanced)
	);
	glBindVertexArray(0);
	Helpers::CheckForGLError();
	m_Mesh.push_back(newMesh);
	return true;
}

bool Model::CreateModel(std::string filename, std::string texturename)
{
	Meshes newMesh;

	Helpers::ModelLoader loader;
	if (!loader.LoadFromFile(filename))
	{
		std::cout << "ERROR NO MODEL" << std::endl;
		return false;
	}

	for (const Helpers::Mesh& mesh : loader.GetMeshVector())
	{

		GLuint positionVBO;
		glGenBuffers(1, &positionVBO);
		glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh.vertices.size(), mesh.vertices.data(), GL_STATIC_DRAW);

		GLuint elementVBO;
		glGenBuffers(1, &elementVBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementVBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * mesh.elements.size(), mesh.elements.data(), GL_STATIC_DRAW);

		newMesh.numElements = mesh.elements.size();

		GLuint NormalVBO;
		glGenBuffers(1, &NormalVBO);
		glBindBuffer(GL_ARRAY_BUFFER, NormalVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * mesh.normals.size(), mesh.normals.data(), GL_STATIC_DRAW);

		GLuint TextureVBO;
		glGenBuffers(1, &TextureVBO);
		glBindBuffer(GL_ARRAY_BUFFER, TextureVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * mesh.uvCoords.size(), mesh.uvCoords.data(), GL_STATIC_DRAW);

		glGenVertexArrays(1, &newMesh.vao);
		glBindVertexArray(newMesh.vao);

		glBindBuffer(GL_ARRAY_BUFFER, positionVBO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(
			0,                  // attribute 0
			3,                  // size in components of each item in the stream e.g. a position has 3 components x,y and z
			GL_FLOAT,           // type of the item
			GL_FALSE,           // normalized or not (advanced)
			0,                  // stride (advanced)
			(void*)0            // array buffer offset (advanced)
		);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementVBO);

		glBindBuffer(GL_ARRAY_BUFFER, NormalVBO);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(
			1,                  // attribute 0
			3,                  // size in components of each item in the stream e.g. a position has 3 components x,y and z
			GL_FLOAT,           // type of the item
			GL_FALSE,           // normalized or not (advanced)
			0,                  // stride (advanced)
			(void*)0            // array buffer offset (advanced)
		);



		glBindBuffer(GL_ARRAY_BUFFER, TextureVBO);
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(
			2,                  // attribute 0
			2,                  // size in components of each item in the stream e.g. a position has 3 components x,y and z
			GL_FLOAT,           // type of the item
			GL_FALSE,           // normalized or not (advanced)
			0,                  // stride (advanced)
			(void*)0            // array buffer offset (advanced)
		);


		Helpers::ImageLoader iloader;
		if (iloader.Load(texturename))
		{
			glGenTextures(1, &newMesh.texture);
			glBindTexture(GL_TEXTURE_2D, newMesh.texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, iloader.Width(), iloader.Height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, iloader.GetData());
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "ERROR NO TEXTURE" << std::endl;
			return false;
		}
	}
	glBindVertexArray(0);
	m_Mesh.push_back(newMesh);
	return true;



}

void Model::Render(Meshes mesh, GLuint m_program)
{
	glBindVertexArray(mesh.vao);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh.texture);
	glUniform1i(glGetUniformLocation(m_program, "sampler_tex"), 0);
	glDrawElements(GL_TRIANGLES, mesh.numElements, GL_UNSIGNED_INT, (void*)0);
}
