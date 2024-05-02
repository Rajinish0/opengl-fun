#ifndef FUNCS_GUARD
#define FUNCS_GUARD

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "stb_image.h"
#include <string>


namespace funcs {
	void genStar(float* verts);



	void getColors(float* colors, int numColors);


	void genSphere(float* arr, float* textarr, int points);

	void genStrips(unsigned int* indicies, int points);

	unsigned int loadTexture(std::string path);

}



#endif