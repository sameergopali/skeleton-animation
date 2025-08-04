 //
//  Model.cpp
//  ogl
//
//  Created by logpoint on 8/9/20.
//

#include "Model.hpp"
#include <iostream>
#include <cstring>


void Model::loadModelR(string path){
      scene = importer.ReadFile(path, aiProcess_Triangulate|aiProcess_FlipUVs|aiProcess_CalcTangentSpace);
      if(!scene || scene->mFlags &  AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode){
          cout << "ERROR" << importer.GetErrorString() << endl;
      }
    
      directory = path.substr(0, path.find_last_of('/'));
      processNodeR(scene->mRootNode,scene);
    
}


void Model::processNodeR(aiNode *node,const aiScene *scene){
    for(unsigned int i=0 ; i < node->mNumMeshes; i++){
        aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
       // aiMesh * mesh = scene->mMeshes[0];
        meshesR.push_back(processMeshR(mesh, scene));
    }
    for(unsigned int i=0; i < node->mNumChildren; i++){
        processNodeR(node->mChildren[i], scene);
    }
}



void Model::Draw(Shader &shader){
    for(unsigned int i = 0; i < meshesR.size(); i++)
             meshesR[i].Draw(shader);
}



MeshRaw Model::processMeshR(aiMesh *mesh, const aiScene *scene ){
    vector<VertexR> vertices;
    vector<unsigned int> indices;
    vector<VertexBoneData> vertexBoneList;
    vector<Texture> textures;
    vertexBoneList.resize(mesh->mNumVertices);

    // walk through each of the mesh's vertices
    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        VertexR vertex;
        glm::vec3 pvector;
        
        pvector.x = mesh->mVertices[i].x;
        pvector.y = mesh->mVertices[i].y;
        pvector.z = mesh->mVertices[i].z;
        vertex.position = pvector;
        
        // normals
        if (mesh->HasNormals())
        {
            vertex.normal.x = mesh->mNormals[i].x;
            vertex.normal.y = mesh->mNormals[i].y;
            vertex.normal.z = mesh->mNormals[i].z;
        }
        else
        {
            vertex.normal = glm::vec3(0.0f, 0.0f, 0.0f);
        }
        
        // texture coordinates
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
        }
        else
            vertex.texCoords = glm::vec2(0.0f, 0.0f);
            
        vertices.push_back(vertex);
       
    }
    aModel.loadBone(mesh, vertexBoneList);
    
    // process indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
    
    // process materials
    if(mesh->mMaterialIndex >= 0)
    {
        aiMaterial *material = scene->mMaterials[mesh->mMaterialIndex];
        // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
        // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER. 
        // Same applies to other texture as the following list summarizes:
        // diffuse: texture_diffuseN
        // specular: texture_specularN
        // normal: texture_normalN

        // 1. diffuse maps
        vector<Texture> diffuseMaps = loadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // 2. specular maps
        vector<Texture> specularMaps = loadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
        // 3. normal maps
        std::vector<Texture> normalMaps = loadMaterialTextures(material, aiTextureType_HEIGHT, "texture_normal");
        textures.insert(textures.end(), normalMaps.begin(), normalMaps.end());
        // 4. height maps
        std::vector<Texture> heightMaps = loadMaterialTextures(material, aiTextureType_AMBIENT, "texture_height");
        textures.insert(textures.end(), heightMaps.begin(), heightMaps.end());
    }
   
    return MeshRaw(vertices, indices, vertexBoneList, textures);
}

vector<Texture> Model::loadMaterialTextures(aiMaterial *mat, aiTextureType type, string typeName)
{
    vector<Texture> textures;
    for(unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        // check if texture was loaded before and if so, continue to next iteration: skip loading a new texture
        bool skip = false;
        for(unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if(std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true; // a texture with the same filepath has already been loaded, continue to next one. (optimization)
                break;
            }
        }
        if(!skip)
        {   // if texture hasn't been loaded already, load it
            Texture texture;
            texture.id = TextureFromFile(str.C_Str(), this->directory);
            texture.type = typeName;
            texture.path = str.C_Str();
            textures.push_back(texture);
            textures_loaded.push_back(texture);  // store it as texture loaded for entire model, to ensure we won't unnecesery load duplicate textures.
        }
    }
    return textures;
}

unsigned int TextureFromFile(const char *path, const string &directory, bool gamma)
{
    string filename = string(path);
    filename = directory + '/' + filename;

    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format = GL_RGB; // default format
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    return textureID;
}


Model::Model(char *path, int type){
    cout<< "loading Raw";
    loadModelR(path);
}

void Model::animate(float time, vector<glm::mat4> &transforms){
    Animator animator(scene);
    animator.setup(scene, aModel.boneMapping,  aModel.boneNum, aModel.perVertexboneInfoList);
    animator.loadAnimationTransform(time, transforms);
}
