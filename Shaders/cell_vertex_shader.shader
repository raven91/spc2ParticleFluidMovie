#version 330

in vec3 position;
in float density;

out VertexShaderOut
{
	float density;
} vs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = vec4(position.xzy, 1.0f);
	gl_PointSize = 1.0f;
	
	vs_out.density = density;
}
