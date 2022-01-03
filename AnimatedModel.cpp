//
//  AnimatedModel.cpp
//  ogl
//
//  Created by logpoint on 8/10/20.
//  Copyright © 2020 logpoint. All rights reserved.
//

#include "AnimatedModel.hpp"
void AnimatedModel::loadBone( const aiMesh *pMesh, vector<VertexBoneData> &Bones){
    
  
    for(uint i =0; i < pMesh->mNumBones ; i++){
        uint boneIndex=0;
        string boneName(pMesh->mBones[i]->mName.data);
       
        if ( boneMapping.find(boneName) == boneMapping.end()) {
            boneIndex = boneNum;
            boneNum++;
            boneInfopv bi;
            perVertexboneInfoList.push_back(bi);
        }
        else {
            boneIndex = boneMapping[boneName];
        }
        boneMapping[boneName] = boneIndex;
        perVertexboneInfoList[boneIndex].boneOffset = aiMatrix4x4ToGlm(pMesh->mBones[i]->mOffsetMatrix);
        

        
        for(uint j=0; j < pMesh->mBones[i]->mNumWeights;j++){
            uint vertexID = pMesh->mBones[i]->mWeights[j].mVertexId;
            float weight =pMesh->mBones[i]->mWeights[j].mWeight;
            Bones[vertexID].AddBoneData(boneIndex, weight);
        }
    }
    
    
    
}

AnimatedModel::AnimatedModel(){
    
}

