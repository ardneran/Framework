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

uniform mat3 norm;
uniform mat4 modelViewPerspective;
//uniform mat4 modelViewOrthographic;
uniform sampler2D normalTextureSampler;

void main()
{
	vPosition = modelViewPerspective * vec4(position, 1.0);
	gl_Position = vPosition;
	vNormal = normalize(norm * normal);
	vTexcoord = texcoord;
}
