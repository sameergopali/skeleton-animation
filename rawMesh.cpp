//
//  rawMesh.cpp
//  ogl
//
//  Created by logpoint on 8/9/20.
//

#include "rawMesh.hpp"

RawMesh::RawMesh() : vertices { -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f,}
{
    initializeVAO();
};
    
    

void RawMesh::initializeVAO(){
    
    unsigned int VBO;
    glGenBuffers(1,&VBO);
    glGenVertexArrays(1,&VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    
    glVertexAttribPointer(0,3,GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
}
void RawMesh::draw(Shader shaderprogram){
    shaderprogram.use();
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES,0,3);    
}
