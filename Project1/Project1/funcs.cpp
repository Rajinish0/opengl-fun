#define STB_IMAGE_IMPLEMENTATION
#include "funcs.h"
#include <cmath>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string.h>
#include <sstream>


namespace funcs {
	void genStar(float* verts) {
		bool yes = true;
		for (int i = 0; i <= 360; i += 36) {
			int ind = (int)(2 * i / 36);
			float factor = (yes) ? 1.0f : 0.5f;
			verts[ind] = cos(glm::radians((float)i)) * factor;
			verts[ind + 1] = sin(glm::radians((float)i)) * factor;
			yes = !yes;
		}
	}


	void getColors(float* colors, int numColors) {
		for (int i = 0; i < numColors; ++i) {
			colors[3 * i] = ((float)(i % 10)) / 10.0;
			colors[3 * i + 1] = ((float)((i + 1) % 10)) / 10.0;
			colors[3 * i + 2] = ((float)((i + 2) % 10)) / 10.0;
		}
	}


	void genSphere(float* arr, float* textarr, int points) {
		float tick = 180.0f / (points - 1);
		float tick2 = 360.0f / (points);

		int p = 0;
		for (float phi = -90; phi < 90 + (tick / 2); phi += tick) {
			for (float theta = 0; theta < 360; theta += tick2) {
				std::string v = "";
				int ind = 3 * points * round((phi + 90) / tick) + round(theta / tick2) * 3;
				arr[ind] = cos(glm::radians(theta)) * (1.5f + cos(glm::radians(phi))) * 0.5f;
				arr[ind + 1] = sin(glm::radians(phi)) * 0.5f;
				arr[ind + 2] = -sin(glm::radians(theta)) * (1.5f + cos(glm::radians(phi))) * 0.5f;

				int ind2 = 2 * points * round((phi + 90) / tick) + round(theta / tick2) * 2;
				textarr[ind2] = (phi + 90.0f) / (180.0f);
				textarr[ind2 + 1] = (theta / (360.0f));
				//arr[ ind    ] = cos(glm::radians(theta)) * cos(glm::radians(phi));
				//arr[ ind + 1] = sin(glm::radians(phi));
				//arr[ ind + 2] = sin(glm::radians(theta)) * cos(glm::radians(phi));
				//std::cout << ind << " "<< phi+90 << " " << tick  << " "<< round((phi + 90)/tick) << round((theta/tick2)) << " "<< theta << std::endl;
				// v += std::to_string(arr[ind])+","+std::to_string(arr[ind+1])+","+std::to_string(arr[ind+2]);
				// std::cout << v << std::endl;
			}
			// ++p;
			// std::cout << p << std::endl;

		}
		// std::cout << p << std::endl;

		 for (int i =0; i<points; ++i){
		 	for (int j =0; j < points; ++j){
		 		std::string v = "";
		 		for (int k =0; k < 2; ++k){
		 			v += std::to_string( textarr[2*(points*i + j) + k] );
		 			v += ",";
		 		}
		 		std::cout << v << std::endl;
		 	}
		 }
	}

	void genStrips(unsigned int* indicies, int points) {
		for (unsigned int i = 0; i < points; ++i) {
			for (unsigned int j = 0; j < points; ++j) {
				int ind = 6 * ((i * (points)) + j);
				indicies[ind] = (i * points + j);
				indicies[ind + 1] = (i * points + (j + 1) % points);
				indicies[ind + 2] = (((i + 1) % points) * points + j);

				indicies[ind + 3] = (i * points + ((j + 1) % points));
				indicies[ind + 4] = (((i + 1) % points) * points + ((j + 1) % points));
				indicies[ind + 5] = (((i + 1) % points) * points + j);
			}
		}
	}

	unsigned int loadTexture(std::string path) {
		int width, height, nrChannels;
		unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);
		unsigned int id;
		glGenTextures(1, &id);
		if (data) {
			GLenum format;
			if (nrChannels == 1)
				format = GL_RED;
			else if (nrChannels == 3)
				format = GL_RGB;
			else if (nrChannels == 4)
				format = GL_RGBA;

			glBindTexture(GL_TEXTURE_2D, id);
			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			stbi_image_free(data);
		}
		else
			std::cout << "Couldn't load texture";

		return id;
	}

}