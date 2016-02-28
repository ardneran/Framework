#ifndef __OBJ_HELPER_H__
#define __OBJ_HELPER_H__

#include "tiny_obj_loader.h"

extern void SortShapes(
    std::vector<tinyobj::shape_t>& out_shapes,
    std::vector<tinyobj::material_t>& out_materials,
    const std::vector<tinyobj::shape_t>& in_shapes,
    const std::vector<tinyobj::material_t>& in_materials);

#endif // __OBJ_HELPER_H__
