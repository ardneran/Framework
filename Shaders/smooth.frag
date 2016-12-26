#version 410 core

in vec3 vPosition;
in vec3 vNormal;
in vec2 vTexcoord;

out vec4 fColor;

//uniform sampler2D ambientTextureSampler;
//uniform sampler2D diffuseTextureSampler;
//uniform sampler2D specularTextureSampler;

void main()
{
	//vec4 ambient = texture(ambientTextureSampler, vTexcoord);
	//vec4 diffuse = texture(diffuseTextureSampler, vTexcoord);
	//vec4 specular = texture(specularTextureSampler, vTexcoord);
	//fColor = (ambient + diffuse + specular);
	//fColor = ambient;
	//fColor = diffuse;
	//fColor = specular;
	fColor = vec4(vNormal, 1.0);
}
