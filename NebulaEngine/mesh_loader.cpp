#include "mesh_loader.h"

Mesh MeshLoader::LoadMesh(const std::string& filePath, bool isZUp)
{
    Assimp::Importer importer;

    // Import the file with Assimp
    const aiScene* scene = importer.ReadFile(filePath,
        aiProcess_Triangulate |          // Ensure all faces are triangles
        aiProcess_JoinIdenticalVertices | // Remove duplicate vertices
        aiProcess_GenSmoothNormals |     // Generate smooth normals
        aiProcess_FlipUVs |              // Flip UVs if needed
        aiProcess_ImproveCacheLocality); // Optimize for GPU cache

    // Check if the file was successfully loaded
    if (!scene || !scene->mRootNode || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) {
        std::cerr << "Error loading file: " << importer.GetErrorString() << std::endl;
        return Mesh(); // Return an empty Mesh on failure
    }

    // Process the first mesh in the scene (you can extend this to handle multiple meshes)
    aiMesh* mesh = scene->mMeshes[0];
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    return ProcessMesh(mesh, material, isZUp);
    
}

Mesh MeshLoader::ProcessMesh(aiMesh* mesh, aiMaterial* aiMaterial, bool isZUp)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;

    Material material;

    // Extract vertices
    for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
        Vertex vertex;

        // Position
        vertex.position = glm::vec3(
            mesh->mVertices[i].x,
            mesh->mVertices[i].y,
            mesh->mVertices[i].z
        );

        // Adjust vertex positions for file formats that use Z-up (e.g. Blender fbx)
        if (isZUp) {
            vertex.position = glm::vec3(vertex.position.x, vertex.position.z, -vertex.position.y);
        }

        // Normal
        if (mesh->HasNormals()) {
            vertex.normal = glm::vec3(
                mesh->mNormals[i].x,
                mesh->mNormals[i].y,
                mesh->mNormals[i].z
            );
        }

        // Adjust vertex normals for file formats that use Z-up (e.g. Blender fbx)
        if (isZUp) {
            vertex.normal = glm::vec3(vertex.normal.x, vertex.normal.z, -vertex.normal.y);
        }

        // Texture coordinates
        if (mesh->mTextureCoords[0]) { // Check if the mesh has texture coordinates
            vertex.textureCoords = glm::vec2(
                mesh->mTextureCoords[0][i].x,
                mesh->mTextureCoords[0][i].y
            );
        }
        else {
            vertex.textureCoords = glm::vec2(0.0f, 0.0f); // Default texture coords
        }

        vertices.push_back(vertex);
    }

    // Extract indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
        aiFace face = mesh->mFaces[i];

        // Each face should be a triangle (due to aiProcess_Triangulate)
        for (unsigned int j = 0; j < face.mNumIndices; j++) {
            indices.push_back(face.mIndices[j]);
        }
    }

    // Extract material properties
    aiColor3D color;
    if (aiMaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS) {
        material.diffuse = glm::vec3(color.r, color.g, color.b);
    }
    if (aiMaterial->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS) {
        material.specular = glm::vec3(color.r, color.g, color.b);
    }
    float shininess;
    if (aiMaterial->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS) {
        material.shininess = shininess;
    }



    // Create and return the Mesh object
    return Mesh(vertices, indices, material);
}
