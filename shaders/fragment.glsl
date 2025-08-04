#version 410 core
out vec4 fragColor;

in vec2 TexCoords;
in vec3 Normal;
in vec3 FragPos;
in vec4 vertexColor;

uniform sampler2D texture_diffuse1;
uniform bool hasTexture;

void main(){
    if (hasTexture) {
        fragColor = texture(texture_diffuse1, TexCoords);
    } else {
        fragColor = vertexColor;
    }
}
