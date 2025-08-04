
#version 410 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in ivec4 BoneIDs;
layout (location = 4) in vec4 Weights;

out vec2 TexCoords;
out vec3 Normal;
out vec3 FragPos;
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
    
    vec4 PosL = BoneTransform * vec4(aPos, 1.0);
    gl_Position = projection * view * model * PosL;
    
    TexCoords = aTexCoords;
    Normal = mat3(transpose(inverse(model))) * aNormal;
    FragPos = vec3(model * PosL);
    vertexColor = vec4(0.10,0.15,0.20,1.0);
}
