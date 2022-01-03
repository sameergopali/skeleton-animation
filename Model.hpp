//
//  Model.hpp
//  ogl
//
//  Created by logpoint on 8/9/20.
//

#ifndef Model_hpp
#define Model_hpp
#include "Shader.h"
#include "Mesh.hpp"
#include <stdio.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "stb_image.h"
#include "MeshRaw.hpp"
#include "AnimatedModel.hpp"
#include <vector>
#include "Animator.hpp"
using namespace std;
class Model{
public:
 
    Model(char *path, int type);
    
    void Draw(Shader &shader);
    
    string directory;
    
    AnimatedModel aModel;
    
   // Animator animator;
    
    void animate(float time, vector<glm::mat4>& transforms);

private:
  
    std::vector<MeshRaw> meshesR;
    
    void loadModelR(string path);
    
    void processNodeR(aiNode *node, const aiScene *scene);
    
    MeshRaw processMeshR(aiMesh *mesh, const aiScene *scene);
    


    glm::mat4 globalInvereMat;

    
    const aiScene* scene;
    
    Assimp::Importer importer;
    
};

#endif /* Model_hpp */
