//
//  rawMesh.hpp
//  ogl
//
//  Created by logpoint on 8/9/20.
//

#ifndef rawMesh_hpp
#define rawMesh_hpp
#define GL_SILENCE_DEPRECATION
#include <stdio.h>
#include "Shader.h"
class RawMesh{
    float vertices[9];
    public:
        unsigned int VAO;
        RawMesh();
        void draw(Shader shaderprogram);
        void initializeVAO();
    
};
#endif /* rawMesh_hpp */
