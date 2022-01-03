//
//  MeshRaw.cpp
//  ogl
//
//  Created by logpoint on 8/10/20.
//  Copyright © 2020 logpoint. All rights reserved.
//

#include "MeshRaw.hpp"

void MeshRaw::Draw(Shader shader){
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);
    
}
void MeshRaw::setupMeshwithBone(){
         glGenVertexArrays(1,&VAO);
         glGenBuffers(1,&VBO);
         glGenBuffers(1,&EBO);
         glGenBuffers(1,&BONE_VB);
         glBindVertexArray(VAO);
         glBindBuffer(GL_ARRAY_BUFFER, VBO);
         glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(VertexR),&vertices[0],GL_STATIC_DRAW);
    
         
         glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(VertexR),(void*)0);
         glEnableVertexAttribArray(0);
         glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
         glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size()*sizeof(unsigned int),&indexes[0], GL_STATIC_DRAW);
    
         glBindBuffer(GL_ARRAY_BUFFER, BONE_VB);
         glBufferData(GL_ARRAY_BUFFER, sizeof(VertexBoneData) * boneData.size(), &boneData[0], GL_STATIC_DRAW);
     
        
        glEnableVertexAttribArray(1);
        glVertexAttribIPointer(1, 4, GL_INT, sizeof(VertexBoneData), (const GLvoid*)0);

        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2,4,GL_FLOAT,GL_FALSE,sizeof(VertexBoneData),(void*)offsetof(VertexBoneData,weights));

    
        glBindVertexArray(0);

}
void MeshRaw::setupMesh(){
            glGenVertexArrays(1,&VAO);
            glGenBuffers(1,&VBO);
            glGenBuffers(1,&EBO);
            glBindVertexArray(VAO);
            glBindBuffer(GL_ARRAY_BUFFER, VBO);
            glBufferData(GL_ARRAY_BUFFER, vertices.size()*sizeof(VertexR),&vertices[0],GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size()*sizeof(unsigned int),&indexes[0], GL_STATIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(VertexR),(void*)0);
    
       
}

MeshRaw::MeshRaw(std::vector<VertexR> vertices,std::vector<unsigned int>indices){
    this->vertices = vertices;
    this->indexes = indices;
    setupMesh();
    
}
MeshRaw::MeshRaw(vector<VertexR> vertices,std::vector<unsigned int>indices,vector<VertexBoneData> boneData){
    this->vertices = vertices;
    this->indexes = indices;
    this->boneData =boneData;
    setupMeshwithBone();
    
}

void VertexBoneData::AddBoneData(uint BoneID, float Weight){
    for (uint i = 0 ; i < 4 ; i++) {
          if (weights[i] == 0.0) {
              IDs[i] = BoneID;
              weights[i] = Weight;
              return;
          }
    }}
