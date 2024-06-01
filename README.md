# opengl-fun

The object loader in model.cpp, mesh.cpp only loads the textures correctly if the whole model uses only one texture. So, either the mtllib needs to be parsed first and give each mesh the correct material based on usemtl or it's better to use assimp.
