//
//  ObjMeshLoader.cpp
//  Framework
//
//  Created by Narendra Umate on 1/9/16.
//
//

#include "ObjMeshLoader.h"

ObjMeshLoader::ObjMeshLoader() {
}

ObjMeshLoader::~ObjMeshLoader() {
}

std::list<VisualSpatial*> ObjMeshLoader::load(const std::string& filepath, const std::string& filebase) {
    std::list<VisualSpatial*> visuals;
	tinyobj::attrib_t attribs;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string error;
    if (LoadObj(&attribs, &shapes, &materials, &error, filepath.c_str(), filebase.c_str())) {
        for (std::vector<tinyobj::shape_t>::iterator it = shapes.begin(); it != shapes.end(); ++it) {
			std::vector<float> positions;
			std::vector<float> normals;
			std::vector<float> texcoords;
			std::vector<unsigned int> indices;
			positions.resize(it->mesh.indices.size() * 3);
			normals.resize(it->mesh.indices.size() * 3);
			texcoords.resize(it->mesh.indices.size() * 2);
			indices.resize(it->mesh.indices.size());
			for (unsigned int i = 0; i < it->mesh.indices.size(); ++i) {
				tinyobj::index_t indicesTuple = it->mesh.indices[i];
				positions[i * 3 + 0] = (attribs.vertices[indicesTuple.vertex_index * 3 + 0]);
				positions[i * 3 + 1] = (attribs.vertices[indicesTuple.vertex_index * 3 + 1]);
				positions[i * 3 + 2] = (attribs.vertices[indicesTuple.vertex_index * 3 + 2]);
				normals[i * 3 + 0] = (attribs.normals[indicesTuple.normal_index * 3 + 0]);
				normals[i * 3 + 1] = (attribs.normals[indicesTuple.normal_index * 3 + 1]);
				normals[i * 3 + 2] = (attribs.normals[indicesTuple.normal_index * 3 + 2]);
				texcoords[i * 2 + 0] = (attribs.texcoords[indicesTuple.texcoord_index * 2 + 0]);
				texcoords[i * 2 + 1] = (attribs.texcoords[indicesTuple.texcoord_index * 2 + 1]);
				indices[i] = (i);
			}
            VisualSpatial* visual = new VisualSpatial(positions, normals, texcoords, indices);
			// Assume that every shape has only one material.
			if (materials.size()) {
				loadMaterial(visual, materials[it->mesh.material_ids[0]], filebase);
			} else {
				tinyobj::material_t material;
				loadMaterial(visual, material, filebase);
			}
            visual->setModelBoundingBox(positions);
            visuals.push_back(visual);
        }
    } else {
        printf("%s", error.c_str());
    }
    return visuals;
}

void ObjMeshLoader::loadMaterial(VisualSpatial* const visual, const tinyobj::material_t& material, const std::string& filebase) {
	Material* currentMaterial = visual->getMaterial();
	if (currentMaterial)
	{
		// TODO Optimize the array copies.
		currentMaterial->ambient[0] = material.ambient[0];
		currentMaterial->ambient[1] = material.ambient[1];
		currentMaterial->ambient[2] = material.ambient[2];
		currentMaterial->diffuse[0] = material.diffuse[0];
		currentMaterial->diffuse[1] = material.diffuse[1];
		currentMaterial->diffuse[2] = material.diffuse[2];
		currentMaterial->specular[0] = material.specular[0];
		currentMaterial->specular[1] = material.specular[1];
		currentMaterial->specular[2] = material.specular[2];
		currentMaterial->transmittance[0] = material.transmittance[0];
		currentMaterial->transmittance[1] = material.transmittance[1];
		currentMaterial->transmittance[2] = material.transmittance[2];
		currentMaterial->emission[0] = material.emission[0];
		currentMaterial->emission[1] = material.emission[1];
		currentMaterial->emission[2] = material.emission[2];

		currentMaterial->shininess = material.shininess;
		currentMaterial->ior = material.ior;
		currentMaterial->dissolve = material.dissolve;
		currentMaterial->illum = material.illum;
		currentMaterial->dummy = material.dummy;

		loadTexture(filebase, material.ambient_texname, currentMaterial->ambient_texname);
		loadTexture(filebase, material.diffuse_texname, currentMaterial->diffuse_texname);
		loadTexture(filebase, material.specular_texname, currentMaterial->specular_texname);
		loadTexture(filebase, material.specular_highlight_texname, currentMaterial->specular_highlight_texname);
		loadTexture(filebase, material.bump_texname, currentMaterial->bump_texname);
		loadTexture(filebase, material.displacement_texname, currentMaterial->displacement_texname);
		loadTexture(filebase, material.alpha_texname, currentMaterial->alpha_texname);
	}
}

void ObjMeshLoader::loadTexture(const std::string& base, const std::string& name, Texture2D*& texture) {
	if (!base.empty() && !name.empty()) {
        texture = m_textureManager->loadTexture(base + name);
    } else {
        texture = NULL;
    }
}
