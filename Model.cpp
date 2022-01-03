 //
//  Model.cpp
//  ogl
//
//  Created by logpoint on 8/9/20.
//

#include "Model.hpp"


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
        cout << node->mNumMeshes;
        aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
       // aiMesh * mesh = scene->mMeshes[0];
        meshesR.push_back(processMeshR(mesh, scene));
    }
    cout << node->mNumChildren;
    for(unsigned int i=0; i < node->mNumChildren; i++){
        cout << "here";
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
        vertices.push_back(vertex);
       
    }
    aModel.loadBone(mesh, vertexBoneList);
    // now wak through each of the mesh's faces (a face is a mesh its triangle) and retrieve the corresponding vertex indices.
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        // retrieve all indices of the face and store them in the indices vector
        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }
   
    return MeshRaw(vertices,indices,vertexBoneList);
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
