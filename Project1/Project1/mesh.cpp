#include "mesh.h"
#include "Perlin.h"


Mesh::Mesh(std::vector<Vertex> verticies,
	std::vector<Texture> textures, 
	std::vector<unsigned int> indicies) {

	this->verticies = verticies;
	this->textures = textures;
	this->indicies = indicies;
	//for (int i = 0; i < verticies.size(); ++i)
		//std::cout << verticies[i].pos.x << " " << verticies[i].pos.y << " " << verticies[i].pos.z << std::endl;
	if (verticies.size() > 0) setUpMesh();
}


void Mesh::setUpMesh() {
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);


	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * verticies.size(), &(verticies[0]), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal) );
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, tCoords));
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indicies.size(), &indicies[0], GL_STATIC_DRAW);
}


void Mesh::draw(Shader& shdr) {

	shdr.use();
	int spec = 0, diff = 0;


	for (int i = 0; i < textures.size(); ++i) {
		if (textures[i].type == "texture_specular") {
			shdr.setInt(textures[i].type + std::to_string(++spec), i);
		}
		else if (textures[i].type == "texture_diffuse") {
			shdr.setInt(textures[i].type + std::to_string(++diff), i);
		}
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, textures[i].id);
	}

	glBindVertexArray(VAO);
	

	glDrawElements(GL_TRIANGLES, indicies.size(), GL_UNSIGNED_INT, 0);

}


unsigned int convertToFlat(unsigned int i, unsigned int j, int total) {
	return (i * total + j);
}



Mesh* genSphereMesh() {
	int points = 100;
	float tick = 180.0f / (points - 1);
	float tick2 = 360.0f / (points);
	std::vector<Vertex> vec;
	std::vector<Texture> t;
	std::vector<unsigned int> indicies;

	int p = 0;
	for (float phi = -90; phi < 90 + (tick / 2); phi += tick) {
		for (float theta = 0; theta < 360; theta += tick2) {
			int i = round((phi + 90) / tick);
			int j = round((theta / tick2));
			//arr[ind] = cos(glm::radians(theta)) * (1.5f + cos(glm::radians(phi))) * 0.5f;
			//arr[ind + 1] = sin(glm::radians(phi)) * 0.5f;
			//arr[ind + 2] = -sin(glm::radians(theta)) * (1.5f + cos(glm::radians(phi))) * 0.5f;

			glm::vec3 p = glm::vec3(cos(glm::radians(theta)) * cos(glm::radians(phi)),
									sin(glm::radians(phi)),
									sin(glm::radians(theta)) * cos(glm::radians(phi)));

			Vertex vert;
			vert.pos = p;
			vert.normal = p;
			vert.tCoords = glm::vec2(0, 0);
			vec.push_back(vert);
			//has a hole but idc for testing 
			indicies.push_back( convertToFlat(i, j, points) );
			indicies.push_back( convertToFlat(i, j+1, points) );
			indicies.push_back( convertToFlat(i+1, j, points) );

			indicies.push_back( convertToFlat(i, j+1, points) );
			indicies.push_back( convertToFlat(i+1, j+1, points) );
			indicies.push_back( convertToFlat(i+1, j, points) );
		}
	}
	return new Mesh(vec, t, indicies);
	//mesh->verticies = vec;
	//mesh->textures = t;
	//mesh->indicies = indicies;
}

Mesh* genTerrainMesh(double xOffset, double zOffset) {

	int points = 100;
	double tick = 20.0f / (points-1);
	double tick2 = 20.0 / (points - 1);
	Perlin2d perlin;

	std::vector<Vertex> vec;
	std::vector<Texture> t;
	std::vector<unsigned int> indicies;

	for (double z = -10.0; z < 10.0 + (tick / 2); z+=tick) {
		for (double x = -10.0; x < 10.0 + (tick2 / 2); x += tick2) {

			Vertex vert;
			//(x + 25) / 10, ((z + 25) / 10) + zOffset
			vert.pos = glm::vec3(x, 4*perlin.noise((x+10)/5, (z+10)/5) + zOffset, z);
			vert.normal = perlin.normal((x+10)/5, (z+10)/5 + zOffset);
			vert.tCoords = glm::vec2(0, 0);
			vec.push_back(vert);
		}
	}

	for (int i = 0; i < points-1; ++i) {
		for (int j = 0; j < points-1; ++j) {
			indicies.push_back( convertToFlat(i, j, points) );
			indicies.push_back( convertToFlat(i, j + 1, points));
			indicies.push_back(convertToFlat(i + 1, j, points));

			indicies.push_back(convertToFlat(i, j + 1, points));
			indicies.push_back(convertToFlat(i + 1, j + 1, points));
			indicies.push_back(convertToFlat(i + 1, j, points));
		}
	}

	return new Mesh(vec, t, indicies);

}


Texture::Texture(std::string tp, unsigned int i)
	:type(tp), id(i) {}