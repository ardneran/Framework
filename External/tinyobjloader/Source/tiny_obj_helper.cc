//
// Stiches multiple .obj files into one .obj.
//
#include "tiny_obj_loader.h"
#include "tiny_obj_helper.h"

// TODO
void SortShapes(
    std::vector<tinyobj::shape_t>& out_shapes,
    std::vector<tinyobj::material_t>& out_materials,
    const std::vector<tinyobj::shape_t>& in_shapes,
    const std::vector<tinyobj::material_t>& in_materials) {
    out_shapes = in_shapes;
    out_materials = in_materials;
}
