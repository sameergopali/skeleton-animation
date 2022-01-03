//
//  AnimatedModel.hpp
//  ogl
//
//  Created by logpoint on 8/10/20.
//  Copyright © 2020 logpoint. All rights reserved.
//

#ifndef AnimatedModel_hpp
#define AnimatedModel_hpp
#include <map>
#include <stdio.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "MeshRaw.hpp"
#include "util.hpp"
using namespace std;
struct boneInfopv{
    glm::mat4 boneOffset;
    glm::mat4 finalTransformation;
};

class AnimatedModel{
public:
    AnimatedModel();
    void loadBone( const aiMesh* pMesh, vector<VertexBoneData>& Bones);
    std::map<string,unsigned int> boneMapping;
    vector<boneInfopv> perVertexboneInfoList;
    uint boneNum=0;

private:

};
#endif /* AnimatedModel_hpp */
