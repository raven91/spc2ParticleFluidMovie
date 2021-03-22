#version 330

#define M_PI        3.14159265358979323846264338327950288   /* pi             */

layout (points) in;
layout (triangle_strip, max_vertices = 24) out;
//uniform mat4 mvp;

in VertexShaderOut
{
    float density;
} gs_in[1];

out GeometryShaderOut
{
    float density;
	float phi;
} gs_out;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 dims;

void main()
{
	mat4 mvp = projection * view * model;
	
	gs_out.density = gs_in[0].density;
	gs_out.phi = gl_in[0].gl_Position.y;

	vec3 cell_center = gl_in[0].gl_Position.xyz;
	float radius_x = 1.0f / dims[0] / 2;
	float radius_y = 1.0f / dims[1] / 2;
	float radius_phi = 2.0f * M_PI / dims[2] / 2;
	
	vec3 A = vec3(cell_center.x - radius_x, cell_center.y + radius_phi, cell_center.z - radius_y);
	vec3 B = vec3(cell_center.x + radius_x, cell_center.y + radius_phi, cell_center.z - radius_y);
	vec3 C = vec3(cell_center.x + radius_x, cell_center.y + radius_phi, cell_center.z + radius_y);
	vec3 D = vec3(cell_center.x - radius_x, cell_center.y + radius_phi, cell_center.z + radius_y);
	vec3 E = vec3(cell_center.x - radius_x, cell_center.y - radius_phi, cell_center.z - radius_y);
	vec3 F = vec3(cell_center.x + radius_x, cell_center.y - radius_phi, cell_center.z - radius_y);
	vec3 G = vec3(cell_center.x + radius_x, cell_center.y - radius_phi, cell_center.z + radius_y);
	vec3 H = vec3(cell_center.x - radius_x, cell_center.y - radius_phi, cell_center.z + radius_y);
	
	// upper face
	gl_Position = mvp * vec4(C, 1.0f); EmitVertex();
	gl_Position = mvp * vec4(D, 1.0f); EmitVertex();
	gl_Position = mvp * vec4(B, 1.0f); EmitVertex();
	gl_Position = mvp * vec4(A, 1.0f); EmitVertex();
	EndPrimitive();

	// lower face
	gl_Position = mvp * vec4(G, 1.0f); EmitVertex();
	gl_Position = mvp * vec4(F, 1.0f); EmitVertex();
	gl_Position = mvp * vec4(H, 1.0f); EmitVertex();
	gl_Position = mvp * vec4(E, 1.0f); EmitVertex();
	EndPrimitive();

	// right face
	gl_Position = mvp * vec4(B, 1.0f); EmitVertex();
	gl_Position = mvp * vec4(F, 1.0f); EmitVertex();
	gl_Position = mvp * vec4(C, 1.0f); EmitVertex();
	gl_Position = mvp * vec4(G, 1.0f); EmitVertex();
	EndPrimitive();

	// left face
	gl_Position = mvp * vec4(A, 1.0f); EmitVertex();
	gl_Position = mvp * vec4(D, 1.0f); EmitVertex();
	gl_Position = mvp * vec4(E, 1.0f); EmitVertex();
	gl_Position = mvp * vec4(H, 1.0f); EmitVertex();
	EndPrimitive();

	// front face
	gl_Position = mvp * vec4(C, 1.0f); EmitVertex();
	gl_Position = mvp * vec4(G, 1.0f); EmitVertex();
	gl_Position = mvp * vec4(D, 1.0f); EmitVertex();
	gl_Position = mvp * vec4(H, 1.0f); EmitVertex();
	EndPrimitive();

	// back face
	gl_Position = mvp * vec4(B, 1.0f); EmitVertex();
	gl_Position = mvp * vec4(A, 1.0f); EmitVertex();
	gl_Position = mvp * vec4(F, 1.0f); EmitVertex();
	gl_Position = mvp * vec4(E, 1.0f); EmitVertex();
	EndPrimitive();

//	mat3 normalMatrix = mat3(transpose(inverse(view * model)));
//	//vec3 normal = normalize(vec3(projection * vec4(normalMatrix * aNormal, 1.0)));
//	gl_Position = vec4(cell_center, 1.0f); EmitVertex();
//	gl_Position = projection * vec4(normalMatrix * vec3(1.0f, 0.0f, 0.0f), 1.0f); EmitVertex();
//	gl_Position = projection * vec4(normalMatrix * vec3(0.0f, 1.0f, 0.0f), 1.0f); EmitVertex();
//	gl_Position = projection * vec4(normalMatrix * vec3(0.0f, 0.0f, 1.0f), 1.0f); EmitVertex();
//	EndPrimitive();
}
