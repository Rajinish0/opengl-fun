//#include "window.h"
//#include "Shader.h"
//#include "funcs.h"
//#include "sun.h"
//#include "camera.h"
//#include "model.h"
//
//Window window{ 800, 600, "my new window" };
//
//// float verts[] = {
//
//// 	//verts       	// colrs
//// 	0.0f, 0.5f,     1.0f, 0.0f, 0.0f,
//// 	0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
////    -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,
//// };
//
//
//float verts[] = {
//	// Back face
//	-0.5f, -0.5f, -0.5f, // Bottom-left
//	 0.5f,  0.5f, -0.5f, // top-right
//	 0.5f, -0.5f, -0.5f, // bottom-right         
//	 0.5f,  0.5f, -0.5f, // top-right
//	-0.5f, -0.5f, -0.5f, // bottom-left
//	-0.5f,  0.5f, -0.5f, // top-left
//	// Front face
//	-0.5f, -0.5f,  0.5f, // bottom-left
//	 0.5f, -0.5f,  0.5f, // bottom-right
//	 0.5f,  0.5f,  0.5f, // top-right
//	 0.5f,  0.5f,  0.5f, // top-right
//	-0.5f,  0.5f,  0.5f, // top-left
//	-0.5f, -0.5f,  0.5f, // bottom-left
//	// Left face
//	-0.5f,  0.5f,  0.5f,
//	-0.5f,  0.5f, -0.5f,
//	-0.5f, -0.5f, -0.5f,
//	-0.5f, -0.5f, -0.5f,
//	-0.5f, -0.5f,  0.5f,
//	-0.5f,  0.5f,  0.5f,
//	// Right face
//	 0.5f,  0.5f,  0.5f,
//	 0.5f, -0.5f, -0.5f,
//	 0.5f,  0.5f, -0.5f,
//	 0.5f, -0.5f, -0.5f,
//	 0.5f,  0.5f,  0.5f,
//	 0.5f, -0.5f,  0.5f,
//	 // Bottom face
//	 -0.5f, -0.5f, -0.5f,
//	  0.5f, -0.5f, -0.5f,
//	  0.5f, -0.5f,  0.5f,
//	  0.5f, -0.5f,  0.5f,
//	 -0.5f, -0.5f,  0.5f,
//	 -0.5f, -0.5f, -0.5f,
//	 // Top face
//	 -0.5f,  0.5f, -0.5f,
//	  0.5f,  0.5f,  0.5f,
//	  0.5f,  0.5f, -0.5f,
//	  0.5f,  0.5f,  0.5f,
//	 -0.5f,  0.5f, -0.5f,
//	 -0.5f,  0.5f,  0.5f,
//};
//
//unsigned int indicies[] = {
//	0, 1, 2, 3, 4, 5
//};
//
//
//float verts2[] = {
//	-0.5f, -0.5f,  0.5f, // bottom-left
//	 0.5f, -0.5f,  0.5f, // bottom-right
//	 0.5f,  0.5f,  0.5f, // top-right
//	 0.5f,  0.5f,  0.5f, // top-right
//	-0.5f,  0.5f,  0.5f, // top-left
//	-0.5f, -0.5f,  0.5f, // bottom-left
//};
//
//// float verts[24] = {0.0f, 0.0f};
//float colors[36 * 3];
//// genStar(newVerts);
//
//
//unsigned int VAO, VBO, EBO, cVBO;
//Shader myShdr{ "vertexLight.glsl", "fragmentLight.glsl" };
//Shader myShdr2 {"vertex.glsl", "fragment.glsl"};
//Shader myShdr3 {"vertex2.glsl", "fragment2.glsl"};
//Shader myShdr4{ "vertexLight.glsl", "myFragment.glsl" };
//Camera cam{ window };
//mySun Sun{ cam, myShdr };
////myEarth Earth {cam, myShdr2};
//std::string path = "D:\\backpack\\backpack.obj";
//std::ifstream f {path};
//Mesh* m;
//
//Model myModel {f};
//
//
//
//
////Sphere mySphere {cam, myShdr3, 30};
//int main() {
//	stbi_set_flip_vertically_on_load(true);
//	m = genSphereMesh();
//	glm::mat4 trans = glm::mat4(1.0f);
//	//trans = glm::scale(trans, glm::vec3(0.3, 0.3, 0.3));
//	//std::cout << "HELLO " << myModel.length() << " ";
//	// glEnable(GL_CULL_FACE);  
//	glEnable(GL_DEPTH_TEST); // check for depth before drawing
//	// glDepthFunc(GL_LEQUAL); // replace pixel if its dist is <= current pixel's dist to the view, default is < 
//	// glCullFace(GL_FRONT);
//	// glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
//	glm::mat4 proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
//
//	// funcs::genStar(&(verts[2]));
//	funcs::getColors(colors, 36);
//	for (int i = 0; i < 24; ++i)
//		std::cout << verts[i] << ",";
//	std::cout << std::endl;
//
//	for (int i = 0; i < 36; ++i)
//		std::cout << colors[i] << ",";
//	std::cout << std::endl;
//
//
//
//	while (!window.shouldClose()) {
//
//		trans = glm::rotate(trans, 0.001f, glm::normalize( glm::vec3(1, 1, 0)) );
//		//glEnable(GL_STENCIL_TEST);
//		//glStencilFunc(GL_ALWAYS, 1, 0xFF);
//		//glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
//		//glStencilMask(0xFF);
//		//Sun.draw(proj);
//
//
//		//glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
//		//glDisable(GL_DEPTH_TEST);
//		//glStencilMask(0x00);
//		//////Sun.Scale(0.01);
//		//Sun.drawScaled(proj, myShdr4);
//		//glStencilMask(0xFF); // to clear the buffer i need to be able to write to it.
//		////glStencilFunc(GL_ALWAYS, 1, 0xFF);
//		//glEnable(GL_DEPTH_TEST);
//		//glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
//
//		myShdr3.setM4("trans", proj*cam.getView()*trans);
//		myShdr3.setVec3("camPos", cam.position);
//		myShdr3.setVec3("lightPos", cam.position);
//		//m->draw(myShdr3);
//		//Earth.draw(proj);
//		myModel.draw(myShdr3);
//
//		//mySphere.draw(proj);
//		// glm::mat4 viewMat = cam.getView();
//		// myShdr.use();
//		// glm::mat4 t = glm::mat4(1.0f);
//		// t = glm::rotate(t, glm::radians((float)glfwGetTime()*10.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 1.0f))) ;
//		// myShdr.setM4("trans", proj*viewMat*t);
//		// glBindVertexArray(VAO);
//		// glDrawArrays(GL_TRIANGLES, 0, 36);
//		// glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0 );
//
//		window.procedure();
//	}
//
//
//}