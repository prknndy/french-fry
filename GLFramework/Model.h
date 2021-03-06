//
//  Model.h
//  GLFramework
//
//  Created by Peter Kennedy on 5/17/16.
//  Copyright (c) 2016 Peter Kennedy. All rights reserved.
//

#ifndef __GLFramework__Model__
#define __GLFramework__Model__

#include <assimp/scene.h>

#include "Mesh.h"

class Model
{
protected:
    //GLuint vao;
    std::vector<Mesh> meshes;
    
    //bool AddMaterialsFromScene(const aiScene* pScene, const std::string& filename);
    bool AddMeshFromScene(unsigned int index, const aiMesh* paiMesh, Material* mat);
    bool ReadScene(const aiScene* pScene, const std::string& filename);
    Material* CreateMaterial(const aiMaterial* pMaterial);
    
public:
    Model();
    ~Model();
    
    bool LoadModel(const std::string& filename);
    virtual void Render();
    virtual void Render(Matrix4f* transform);
    virtual void Render(Vector3 pos, Vector3 rot, Vector3 scale);
    
    // Util
    bool CreateQuad();
};

#endif /* defined(__GLFramework__Model__) */
