#version 410 core

layout( location = 0 ) in vec3 position;
layout( location = 1 ) in vec3 normal;
layout( location = 2 ) in vec2 texcoord;

out vec3 vPosition;
out vec3 vNormal;
out vec2 vTexcoord;

uniform mat3 norm;
uniform mat4 modelViewPerspective;
//uniform mat4 modelViewOrthographic;
uniform sampler2D normalTextureSampler;

void main()
{
	gl_Position = modelViewPerspective * vec4(position, 1.0);
	vPosition = gl_Position.xyz;
	vTexcoord = texcoord;
	vNormal = normalize(norm * normal);
}
