//
//  Animator.hpp
//  ogl
//
//  Created by logpoint on 8/11/20.
//  Copyright © 2020 logpoint. All rights reserved.
//

#ifndef Animator_hpp
#define Animator_hpp

#include <stdio.h>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "Model.hpp"
#include "util.hpp"
#include <map>
using namespace std;

class  Animator{
public:    
    const aiNodeAnim* FindNodeAnim(const aiAnimation* pAnimation, const string NodeName);
    void readAnimation(float AnimationTime, const aiNode* pnode, glm::mat4& parentT);
    void loadAnimationTransform(float TimeinSeconds, vector<glm::mat4>&);
    Animator(const string path);
    Animator(const aiScene *_pScene);
    Assimp::Importer importer;
    map<string, glm::mat4> nodeTransformationsMap;
    void setup( const aiScene *pScene,map<string,uint> boneMap,  uint boneCount,vector<boneInfopv> boneInfoList);
private:
    uint boneCount;
    vector<boneInfopv> boneInfoList;
    const aiScene *pScene;
    map<string,uint> boneMap;
    glm::mat4 globalInverseTransfrom;
    glm::mat4 globalTransform;
    
    void CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    void CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    void CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim);
    uint FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim);
    uint FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim);
    uint FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim);
};

#endif /* Animator_hpp */
