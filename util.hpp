//
//  util.hpp
//  ogl
//
//  Created by logpoint on 8/14/20.
//  Copyright © 2020 logpoint. All rights reserved.
//

#ifndef util_hpp
#define util_hpp

#include <stdio.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
glm::mat4 aiMatrix4x4ToGlm(const aiMatrix4x4 &from);
glm::mat4 aiScaleToGlm(aiVector3D scaleV);
glm::mat4 aiTranslatetoGlm(aiVector3D tanslateV);
glm::mat4 aiQuaterniontoGlm(aiQuaternion roation);
#endif /* util_hpp */
