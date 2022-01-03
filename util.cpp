//
//  util.cpp
//  ogl
//
//  Created by logpoint on 8/14/20.
//  Copyright © 2020 logpoint. All rights reserved.
//

#include "util.hpp"

glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4 &from){
    
    
    /*
     assimp
        a1 a2 a3 a4
        b1 b2 b3 b4
        c1 c2 c3 c4
        d1 d2 d3 d4
     
    glm
        1  0  0  0
        0  1  0  0
        0  0  1  0
        Tx Ty Tz 1
     */
    glm::mat4 to;
    to[0][0]=from.a1;
    to[0][1]=from.b1;
    to[0][2]=from.c1;
    to[0][3]=from.d1;
    
    to[1][0]=from.a2;
    to[1][1]=from.b2;
    to[1][2]=from.c2;
    to[1][3]=from.d2;
    
    to[2][0]=from.a3;
    to[2][1]=from.b3;
    to[2][2]=from.c3;
    to[2][3]=from.d3;
    
    to[3][0]=from.a4;
    to[3][1]=from.b4;
    to[3][2]=from.c4;
    to[3][3]=from.d4;
    return to;
}


glm::mat4 aiScaleToGlm(aiVector3D scaleV){
    return glm::scale(glm::mat4(1.0f), glm::vec3(scaleV.x,scaleV.y,scaleV.z));
}
glm::mat4 aiTranslatetoGlm(aiVector3D translateV){
    return glm::translate(glm::mat4(1.0f), glm::vec3(translateV.x,translateV.y, translateV.z));
}
glm::mat4 aiQuaterniontoGlm(aiQuaternion roation){
    glm::quat quaternion =glm::quat(roation.w,roation.x,roation.y,roation.z);
    return glm::toMat3(quaternion);
    
}
