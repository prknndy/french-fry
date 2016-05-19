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
#include "MaterialManager.h"

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
        // the mesh
        const aiMesh* paiMesh = pScene->mMeshes[i];
        
        
        // the material
        const aiMaterial* paiMaterial = pScene->mMaterials[paiMesh->mMaterialIndex];
        aiString aiMatName;
        paiMaterial->Get(AI_MATKEY_NAME, aiMatName);
        string matName = aiMatName.C_Str();
        
        Material* mat;
        
        mat = MaterialManager::GetInstance()->GetMaterial(matName);
        if (mat == NULL)
        {
            LogDebug("No material found, attempting to create new material");
            mat = CreateMaterial(paiMaterial);
            
            if (mat == NULL)
            {
                LogDebug("Material creation failed, using default");
                mat = MaterialManager::GetInstance()->GetDefaultMaterial();
            }
        }
        
        // the creation
        AddMeshFromScene(i, paiMesh, mat);
    }
    
    return true;
}

bool Model::AddMeshFromScene(unsigned int index, const aiMesh* paiMesh, Material* mat)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    
    const aiVector3D Zero3D(0.0f, 0.0f, 0.0f);
    const aiColor4D White(1.0f, 1.0f, 1.0f, 1.0f);
    
    for (int i = 0; i < paiMesh->mNumVertices; i++)
    {
        // TODO: ignoring normals
        const aiVector3D* pPos = &(paiMesh->mVertices[i]);
        const aiVector3D* pNormal = paiMesh->HasNormals() ? &(paiMesh->mNormals[i]) : &Zero3D;
        const aiVector3D* pTexCoord = paiMesh->HasTextureCoords(0) ? &(paiMesh->mTextureCoords[0][i]) : &Zero3D;
        const aiColor4D* pColor = paiMesh->HasVertexColors(0) ? &(paiMesh->mColors[0][i]) : &White;
        
        Vertex v(Vector3(pPos->x, pPos->y, pPos->z), Vector3(pColor->r, pColor->g, pColor->b), Vector2(pTexCoord->x, pTexCoord->y));
        
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
    meshes[index].SetMaterial(mat);
    
    return true;
}

Material* Model::CreateMaterial(const aiMaterial* pMaterial)
{
    if (pMaterial->GetTextureCount(aiTextureType_DIFFUSE) > 0)
    {
        aiString texturePath;
        if (pMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &texturePath) == AI_SUCCESS)
        {
            string fullPath = "./Textures/";
            fullPath.append(texturePath.data);
            
            aiString aiMatName;
            pMaterial->Get(AI_MATKEY_NAME, aiMatName);
            string matName = aiMatName.C_Str();
            
            if (matName.empty())
            {
                matName = texturePath.C_Str();
            }
            
            return MaterialManager::GetInstance()->CreateMaterial(matName, fullPath);
        }
    }
    
    return NULL;
}

// Partial code to load materials as group, kept for reference
/*bool Model::AddMaterialsFromScene(const aiScene* pScene, const std::string& filename)
{
    bool ret = true;
    for (unsigned int i = 0; i < pScene->mNumMaterials; i++)
    {
        const aiMaterial* pMaterial = pScene->mMaterials[i];
        
    }
    return ret;
}*/


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