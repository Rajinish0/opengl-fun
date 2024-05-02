#include "model.h"
#include "mesh.h"
#include "funcs.h"




Model::Model(std::ifstream& file, unsigned int len, unsigned int len2, unsigned int len3) {
	std::string line;
	std::string token;
	float v1, v2, v3;
	unsigned int i1, i2, i3;
	char sl1, sl2;


	std::vector<Vertex> verticies;
	std::vector<Texture> textures;
	std::vector<unsigned int> indicies;


	std::vector<glm::vec3> vertexNormals;
	std::vector<glm::vec2> tCoords;


	while (std::getline(file, line)) {
		std::stringstream thisLine( line );
		thisLine >> token;


		if (token == "v") {
			thisLine >> v1 >> v2 >> v3;
			Vertex v; 
			v.pos = glm::vec3(1-v1, v2, v3);
			verticies.push_back(v);
		}

		else if (token == "vn") {
			thisLine >> v1 >> v2 >> v3;
			vertexNormals.push_back(glm::vec3(v1, v2, v3));
		}

		else if (token == "vt") {
			thisLine >> v1 >> v2;
			tCoords.push_back(glm::vec2(v1, v2));
		}

		else if (token == "f") {
			/*
			* TODO:
			* So this need not necessarily be 3 in general, what I have to do is
			* given a poly of sides n, i have to create it using triangles. 
			* that means more indicies
			* so say i have 5 fs [i1, i2, i3, i4, i5]
			* i'll need to append [i1, i2, i3], [i2, i3, i4], [i3, i4, i5]
			* basically imagine this is a conv with a 1x3 filter.
			* i could create a vector and append the indicies to that and then finally append these
			* triangles to my final indicies array. But I'll do that some other time when I need more models, this works alright for now.
			*/

			for (int i = 0; i < 3; ++i) {
				thisLine >> i1 >> sl1;
				
				if (thisLine.peek() != '/') {
					thisLine >> i2;
					thisLine >> sl2;
					verticies[i1 - len - 1].tCoords = tCoords[i2 - len2 - 1];
				}
				else { thisLine >> sl2; }

				thisLine >> i3;
				verticies[i1 - len - 1].normal = vertexNormals[i3 - len3 - 1];
				indicies.push_back(i1 - len - 1);

			}
		}

		else if (token == "o") {
			this->child = new Model(file, verticies.size() + len, tCoords.size() + len2, vertexNormals.size() + len3);
			this->meshObj = new Mesh(verticies, textures, indicies);
			std::cout << verticies.size() << " " << std::endl;
		}

		else if (token == "mtllib") {
			thisLine >> token;

			std::cout << "loading Texture " << token << std::endl;


			/*
			* TODO:
			* Accept directory as an argument
			*/
			textures = loadTextures("D:\\backpack\\" + token);
		}
	}

	if (!this->meshObj) { this->meshObj = new Mesh(verticies, textures, indicies); }
}


Model::~Model() {
	delete this->child;
	delete this->meshObj;
}


void Model::draw(Shader& shdr, int k) {
	//std::cout << "HEY " << this->child->meshObj->verticies.size() << std::endl;
	this->meshObj->draw(shdr);
	if (this->child) this->child->draw(shdr);
}

int Model::length() {
	return (this->child) ? this->child->length() + 1 : 1;
}



std::vector<Texture> loadTextures(std::string path) {
	std::ifstream file{ path };
	std::string line;
	std::string token;
	std::string fileName;
	std::vector<Texture> textures;

	while (std::getline(file, line)) {
		std::stringstream thisLine {line};

		thisLine >> token;

		if (token == "map_Kd") {
			thisLine >> fileName;

			std::cout << "loading " << fileName << std::endl;

			Texture tx {"texture_diffuse", funcs::loadTexture("D:\\backpack\\" + fileName)};
			textures.push_back(tx);
		}


		else if (token == "map_Ks") {
			thisLine >> fileName;

			std::cout << "loading " << fileName << std::endl;

			Texture tx {"texture_specular", funcs::loadTexture("D:\\backpack\\" + fileName)};
			textures.push_back(tx);

		}



	}

	return textures;

}







