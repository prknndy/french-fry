//
//  Model.cpp
//  GLFramework
//
//  Created by Peter Kennedy on 5/17/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#include "Model.h"
#include "Math3D.h"
#include "Util.h"

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

Model::Model()
{
    
}

Model::~Model()
{
    
}

bool Model::ReadScene(const aiScene* pScene, const std::string& filename)
{
    meshes.resize(pScene->mNumMeshes);
    
    for (int i = 0; i < meshes.size(); i++)
    {
        const aiMesh* paiMesh = pScene->mMeshes[i];
        AddMeshFromScene(i, paiMesh);
    }
    
    return true;
}

bool Model::AddMeshFromScene(unsigned int index, const aiMesh* paiMesh)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
    
    for (int i = 0; i < paiMesh->mNumVertices; i++)
    {
        // TODO: ignoring normals, not reading colors
        const aiVector3D* pPos = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal = paiMesh->HasNormals() ? &(paiMesh->mNormals[i]) : &Zero3D;
        const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
        
        Vertex v(Vector3(pPos->x, pPos->y, pPos->z), Vector3(1.0f, 1.0f, 1.0f), Vector2(pTexCoord->x, pTexCoord->y));
        
        vertices.push_back(v);
    }
    
     for (unsigned int i = 0 ; i < paiMesh->mNumFaces ; i++)
     {
         const aiFace& face = paiMesh->mFaces[i];
         assert(face.mNumIndices == 3);
         indices.push_back(face.mIndices[0]);
         indices.push_back(face.mIndices[1]);
         indices.push_back(face.mIndices[2]);
     }
    
    meshes[index].Create(vertices, indices);
    
    return true;
}


bool Model::LoadModel(const std::string& filename)
{
    
    bool ret = false;
    
    Assimp::Importer importer;
    const aiScene* pScene = importer.ReadFile(filename.c_str(), aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
    
    if (pScene)
    {
        ret = ReadScene(pScene, filename);
    }
    else
    {
        LogError("Failed to open model file");
    }
    
    return ret;
    
}

void Model::Render()
{
    for (int i = 0; i < meshes.size(); i++)
    {
        meshes[i].Render();
    }
}