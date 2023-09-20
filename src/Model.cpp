#include "Model.hpp"

#include <memory>

#include <glm/glm.hpp>

#include "Vertex.hpp"

Model::Model(const std::string& modelFile)
{
    Assimp::Importer importer;
    const aiScene* scene =
        importer.ReadFile(modelFile, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals);

    if (scene && scene->mRootNode) {
        ProcessNode(scene->mRootNode, scene);
    }
}

void Model::Draw(const Renderer& renderer)
{
    for (auto& mesh : m_meshes) {
        mesh.Draw(renderer);
    }
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    for (unsigned int i = 0; i < node->mNumMeshes; i++) {
        auto mesh = scene->mMeshes[node->mMeshes[i]];
        m_meshes.emplace_back(ProcessMesh(mesh, scene));
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++) {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<VertexPosNormal> vertices;
    std::vector<unsigned int> indices;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        auto position = mesh->mVertices[i];
        auto normal = mesh->mNormals[i];

        VertexPosNormal vertex = {};
        vertex.position = glm::vec3(position.x, position.y, position.z);
        vertex.normal = glm::vec3(normal.x, normal.y, normal.z);

        vertices.emplace_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        auto& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    BufferLayout layout;
    layout.PushAttribute<glm::vec3>();
    layout.PushAttribute<glm::vec3>();

    std::unique_ptr<VertexBuffer> vbo =
        std::make_unique<VertexBuffer>(reinterpret_cast<float*>(&vertices[0]), sizeof(VertexPosNormal) * vertices.size());

    vbo->SetLayout(layout);

    std::unique_ptr<IndexBuffer> ebo = std::make_unique<IndexBuffer>(&indices[0], indices.size());

    std::unique_ptr<VertexArray> vao = std::make_unique<VertexArray>();
    vao->AddVertexBuffer(*vbo);
    vao->SetIndexBuffer(std::move(ebo));

    Mesh m(std::move(vao));
    return m;
}
