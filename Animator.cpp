//
//  Animator.cpp
//  ogl
//
//  Created by logpoint on 8/11/20.
//  Copyright © 2020 logpoint. All rights reserved.
//

#include "Animator.hpp"




const aiNodeAnim* Animator::FindNodeAnim(const aiAnimation* pAnimation, const string NodeName)
{
    for (uint i = 0 ; i < pAnimation->mNumChannels ; i++) {
        const aiNodeAnim* pNodeAnim = pAnimation->mChannels[i];

        if (string(pNodeAnim->mNodeName.data) == NodeName) {
            return pNodeAnim;
            }
}
     return NULL;
}
/*
 1  0  0 0
 0  0  1 0
 0 -1  0 0
 0  0  0 1
 */

void Animator::loadAnimationTransform( float timeinSeconds, vector<glm::mat4> &Transform){

    const aiNode* mRootNode= pScene->mRootNode;
    globalTransform= aiMatrix4x4ToGlm(mRootNode->mTransformation);
    globalInverseTransfrom = glm::inverse(globalTransform);
    
    float TicksPerSecond = pScene->mAnimations[0]->mTicksPerSecond != 0 ?
                           pScene->mAnimations[0]->mTicksPerSecond : 25.0f;
    float TimeInTicks = timeinSeconds * TicksPerSecond;
    float AnimationTime = fmod(TimeInTicks, pScene->mAnimations[0]->mDuration);
    glm::mat4 identity(1);
    readAnimation(AnimationTime, mRootNode, identity);
    
    Transform.resize(boneCount);
    for (uint i = 0 ; i < boneCount ; i++) {
        Transform[i] = boneInfoList[i].finalTransformation;
    }

}

void Animator::readAnimation( float AnimationTime, const aiNode *pNode, glm::mat4 &parentT){
    
    string nodeName(pNode->mName.data);
    glm::mat4 nodeTransformation = aiMatrix4x4ToGlm(pNode->mTransformation);
    const aiAnimation* anim= pScene->mAnimations[0];
    const aiNodeAnim * aNode = FindNodeAnim(anim,nodeName);
    if(aNode){
        aiVector3D Scaling;
        CalcInterpolatedScaling(Scaling, AnimationTime, aNode);
        glm::mat4 scaleM = aiScaleToGlm(Scaling);
        
        aiVector3D Translation;
        CalcInterpolatedPosition(Translation, AnimationTime, aNode);
        glm::mat4 transM = aiTranslatetoGlm(Translation);
       
        aiQuaternion RotationQ;
        CalcInterpolatedRotation(RotationQ, AnimationTime, aNode);
        
        glm::mat4 rotationM = aiQuaterniontoGlm(RotationQ);
        nodeTransformation= transM * rotationM * scaleM;
        
    }
    glm::mat4 globalTransformation =  parentT* nodeTransformation;
   // nodeTransformationsMap[nodeName]= globalTransformation;
    if(boneMap.find(nodeName) != boneMap.end()){
        uint boneId = boneMap[nodeName];
        boneInfoList[boneId].finalTransformation = globalTransformation * boneInfoList[boneId].boneOffset;
        
    }

    
    for(int i=0 ; i < pNode->mNumChildren; i++){
        readAnimation(AnimationTime, pNode->mChildren[i], globalTransformation);
    }
    
    
}

Animator::Animator(const string path):pScene(importer.ReadFile(path, aiProcess_Triangulate|aiProcess_FlipUVs|aiProcess_CalcTangentSpace)){
     
    
}
void Animator::CalcInterpolatedScaling(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    if (pNodeAnim->mNumScalingKeys == 1) {
        Out = pNodeAnim->mScalingKeys[0].mValue;
        return;
    }

    uint ScalingIndex = FindScaling(AnimationTime, pNodeAnim);
    uint NextScalingIndex = (ScalingIndex + 1);
    assert(NextScalingIndex < pNodeAnim->mNumScalingKeys);
    float DeltaTime = (float)(pNodeAnim->mScalingKeys[NextScalingIndex].mTime - pNodeAnim->mScalingKeys[ScalingIndex].mTime);
   // float indexfirst = (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime;
    float Factor = (AnimationTime - (float)pNodeAnim->mScalingKeys[ScalingIndex].mTime) / DeltaTime;
    if(Factor < 0.0f){
        Factor = 0.0f;
    }
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiVector3D& Start = pNodeAnim->mScalingKeys[ScalingIndex].mValue;
    const aiVector3D& End   = pNodeAnim->mScalingKeys[NextScalingIndex].mValue;
    aiVector3D Delta = End - Start;
    Out = Start + Factor * Delta;
}

void Animator::CalcInterpolatedRotation(aiQuaternion& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    // we need at least two values to interpolate...
    if (pNodeAnim->mNumRotationKeys == 1) {
        Out = pNodeAnim->mRotationKeys[0].mValue;
        return;
    }
    
    uint RotationIndex = FindRotation(AnimationTime, pNodeAnim);
    uint NextRotationIndex = (RotationIndex + 1);
    assert(NextRotationIndex < pNodeAnim->mNumRotationKeys);
    float DeltaTime = (float)(pNodeAnim->mRotationKeys[NextRotationIndex].mTime - pNodeAnim->mRotationKeys[RotationIndex].mTime);
    
    float Factor = (AnimationTime - (float)pNodeAnim->mRotationKeys[RotationIndex].mTime) / DeltaTime;
    if(Factor < 0.0f){
           Factor = 0.0f;
       }
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiQuaternion& StartRotationQ = pNodeAnim->mRotationKeys[RotationIndex].mValue;
    const aiQuaternion& EndRotationQ   = pNodeAnim->mRotationKeys[NextRotationIndex].mValue;
    aiQuaternion::Interpolate(Out, StartRotationQ, EndRotationQ, Factor);
    Out = Out.Normalize();
}

void Animator::CalcInterpolatedPosition(aiVector3D& Out, float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    if (pNodeAnim->mNumPositionKeys == 1) {
        Out = pNodeAnim->mPositionKeys[0].mValue;
        return;
    }
            
    uint PositionIndex = FindPosition(AnimationTime, pNodeAnim);
    uint NextPositionIndex = (PositionIndex + 1);
    assert(NextPositionIndex < pNodeAnim->mNumPositionKeys);
    float DeltaTime = (float)(pNodeAnim->mPositionKeys[NextPositionIndex].mTime - pNodeAnim->mPositionKeys[PositionIndex].mTime);
    float indexfist =(float)pNodeAnim->mPositionKeys[PositionIndex].mTime;
    float Factor = (AnimationTime - (float)pNodeAnim->mPositionKeys[PositionIndex].mTime) / DeltaTime;
    if(Factor < 0.0f){
           Factor = 0.0f;
       }
    assert(Factor >= 0.0f && Factor <= 1.0f);
    const aiVector3D& Start = pNodeAnim->mPositionKeys[PositionIndex].mValue;
    const aiVector3D& End = pNodeAnim->mPositionKeys[NextPositionIndex].mValue;
    aiVector3D Delta = End - Start;
    Out = Start + Factor * Delta;
}

uint Animator::FindPosition(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    for (uint i = 0 ; i < pNodeAnim->mNumPositionKeys - 1 ; i++) {
        if (AnimationTime < (float)pNodeAnim->mPositionKeys[i + 1].mTime) {
            return i;
        }
    }
    
    assert(0);

    return 0;
}


uint Animator::FindRotation(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    assert(pNodeAnim->mNumRotationKeys > 0);

    for (uint i = 0 ; i < pNodeAnim->mNumRotationKeys - 1 ; i++) {
        if (AnimationTime < (float)pNodeAnim->mRotationKeys[i + 1].mTime) {
            return i;
        }
    }
    
    assert(0);

    return 0;
}


uint Animator::FindScaling(float AnimationTime, const aiNodeAnim* pNodeAnim)
{
    assert(pNodeAnim->mNumScalingKeys > 0);
    
    for (uint i = 0 ; i < pNodeAnim->mNumScalingKeys - 1 ; i++) {
        if (AnimationTime < (float)pNodeAnim->mScalingKeys[i + 1].mTime) {
            return i;
        }
    }
    
    assert(0);

    return 0;
}

void Animator::setup(const aiScene *_pScene, map<string, uint> boneMap, uint boneCount, vector<boneInfopv> boneInfoList) {
    this->boneMap = boneMap;
    this->boneCount= boneCount;
    this->boneInfoList = boneInfoList;
}

Animator::Animator(const aiScene *_pScene):pScene(_pScene){
   
}
