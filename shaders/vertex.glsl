
#version 410 core
layout (location = 0) in vec3 aPos;
layout (location =1 ) in ivec4 BoneIDs;
layout (location =2)  in vec4 Weights;
out vec4 vertexColor;
const int MAX_BONES = 100;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform mat4 mvp[3];
uniform mat4 gBones[MAX_BONES];
uniform mat4 nodeTransform;
void main(){
    mat4 BoneTransform = gBones[BoneIDs[0]] * Weights[0];
   BoneTransform += gBones[BoneIDs[1]] * Weights[1];
   BoneTransform += gBones[BoneIDs[2]] * Weights[2];
  BoneTransform += gBones[BoneIDs[3]] * Weights[3];
   // vec4 PosL = vec4(aPos, 1.0);
   vec4 PosL = BoneTransform * vec4(aPos, 1.0);
  //  gl_Position = mvp[0] * mvp[1] * mvp[2]* nodeTransform* PosL;
    gl_Position = projection * view * model*  PosL;
    vertexColor = vec4(0.5,0.5,0.5,1.0);
    
}
