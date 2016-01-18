//
// http://http.developer.nvidia.com/CgTutorial/cg_tutorial_chapter05.html
// C5E2v_fragmentLighting
//

#version 410 core

layout( location = 0 ) in vec3 position;
layout( location = 1 ) in vec3 normal;
layout( location = 2 ) in vec2 texcoord;

out vec4 vPosition;
out vec3 vNormal;
out vec2 vTexcoord;

uniform mat4 worldViewProjection;
uniform mat3 worldView;

void main()
{
	gl_position = worldViewProjection * vec4(position, 1.0);
	vPosition = gl_position;
	vNormal = mat3(worldView) * normal;
	vTexcoord = texcoord;
}
