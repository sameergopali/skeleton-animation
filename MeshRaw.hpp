//
//  MeshRaw.hpp
//  ogl
//
//  Created by logpoint on 8/10/20.
//  Copyright © 2020 logpoint. All rights reserved.
//

#ifndef MeshRaw_hpp
#define MeshRaw_hpp
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "Shader.h"
#include<glad/glad.h>

#include <stdio.h>
#define NUM_BONE_PER_VERTEX 4
using namespace std;

struct VertexBoneData{
    uint IDs[NUM_BONE_PER_VERTEX];
    float weights[NUM_BONE_PER_VERTEX]={0.0f};
    void AddBoneData(uint BoneID, float Weight);
};
struct VertexR{
    glm::vec3 position;
};

class MeshRaw{
public:
        vector<VertexR> vertices;
        vector<VertexBoneData> boneData;
        vector<unsigned int> indexes;
        unsigned int VAO;
        
        MeshRaw(vector<VertexR> vertices,std::vector<unsigned int>indices);
        MeshRaw(vector<VertexR> vertices,std::vector<unsigned int>indices,vector<VertexBoneData> boneData);
        void Draw(Shader shader);
private:
        unsigned int VBO, EBO, BONE_VB;
        void setupMesh();
        void setupMeshwithBone();
    
};
#endif /* MeshRaw_hpp */
