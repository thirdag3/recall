#include "Model.hpp"

#include <memory>

#include <glm/glm.hpp>

#include "Texture.hpp"
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
    std::vector<VertexPosNormalTexture> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> diffuseTextures;

    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        auto position = mesh->mVertices[i];
        auto normal = mesh->mNormals[i];
        auto uv = mesh->mTextureCoords[0][i];

        VertexPosNormalTexture vertex = {};
        vertex.position = glm::vec3(position.x, position.y, position.z);
        vertex.normal = glm::vec3(normal.x, normal.y, normal.z);
        vertex.uv = glm::vec2(uv.x, uv.y);

        vertices.emplace_back(vertex);
    }

    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        auto& face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    if (mesh->mMaterialIndex >= 0)
    {
        auto& material = scene->mMaterials[mesh->mMaterialIndex];
        diffuseTextures = LoadTexturesFromMaterial(material, aiTextureType_DIFFUSE, scene);
    }

    std::shared_ptr<Material> meshMaterial = std::make_shared<Material>(std::move(diffuseTextures[0]));

    BufferLayout layout;
    layout.PushAttribute<glm::vec3>();
    layout.PushAttribute<glm::vec3>();
    layout.PushAttribute<glm::vec2>();

    std::unique_ptr<VertexBuffer> vbo = std::make_unique<VertexBuffer>(
        reinterpret_cast<float*>(&vertices[0]), sizeof(VertexPosNormalTexture) * vertices.size());

    vbo->SetLayout(layout);

    std::unique_ptr<IndexBuffer> ebo = std::make_unique<IndexBuffer>(&indices[0], indices.size());

    std::unique_ptr<VertexArray> vao = std::make_unique<VertexArray>();
    vao->AddVertexBuffer(*vbo);
    vao->SetIndexBuffer(std::move(ebo));

    Mesh m(std::move(vao), meshMaterial);
    return m;
}

std::vector<Texture> Model::LoadTexturesFromMaterial(aiMaterial* material, aiTextureType type, const aiScene* scene)
{
    std::vector<Texture> textures;

    aiString textureFile;
    material->Get(AI_MATKEY_TEXTURE(type, 0), textureFile);

    if (auto assimpTexture = scene->GetEmbeddedTexture(textureFile.C_Str())) {
        Image image(static_cast<int>(assimpTexture->mWidth), static_cast<int>(assimpTexture->mHeight), 0,
            reinterpret_cast<unsigned char*>(assimpTexture->pcData));

        Texture texture(image);
        textures.push_back(std::move(texture));
    }

    return textures;
}
