//
//  model.hpp
//  LearnOpenGL
//
//  Created by hsbcnet.mobile.uk hsbcnet.mobile.uk on 2019/3/28.
//  Copyright © 2019年 chensx. All rights reserved.
//

#ifndef model_hpp
#define model_hpp

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "stb_image.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "mesh.hpp"
#include "Shader.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma = false);

class Model {
public:
    vector<Texture> textures_loaded;
    vector<Mesh> meshes;
    string directory;
    bool gammaCorrection;
    
    Model(string const &path, bool gamma = false);
    
    void draw(Shader shader);
    
private:
    
    void loadModel(string const &path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName);
    
};

#endif /* model_hpp */
