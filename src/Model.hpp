#pragma once

#include <string>

#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include "Renderer.hpp"

#include "Mesh.hpp"

class Model
{
  public:
    Model(const std::string& modelFile);
    void Draw(const Renderer& renderer);

  private:
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Mesh> m_meshes;
};
