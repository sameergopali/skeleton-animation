//
//  Mesh.hpp
//  ogl
//
//  Created by logpoint on 8/9/20.
//

#ifndef Mesh_hpp
#define Mesh_hpp
#include <glm/glm.hpp>
#include <vector>
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include "Shader.h"
#include<glad/glad.h>

#include <stdio.h>
struct Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoords;
    glm::vec3 Tangent;
    glm::vec3 Bitangent;
    
};
struct Texture{
    unsigned int id;
    std::string type;
    std::string path;
};
class Mesh{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indexes;
    std::vector<Texture>  textures;
    unsigned int VAO;
    
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int>indices, std::vector<Texture> texture);
    void Draw(Shader shader);
private:
    unsigned int VBO, EBO;
    void setupMesh();    
};

#endif /* Mesh_hpp */
