#version 330

layout (location = 0) in vec3 Position;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 Normal;
layout (location = 3) in vec3 Color;
layout (location = 6) in vec3 Tangent;

uniform mat4 gWVP;
uniform mat4 gWorld;
uniform float gtexCount;

out vec2 TexCoord0;
out vec2 TexCoord1;
out vec3 WorldPos0;
out mat3 NormalMatrix;

void main()
{
	vec3 Normal0;

	gl_Position = gWVP * vec4(Position, 1.0);
	Normal0 = normalize((gWorld * vec4(Normal, 0.0)).xyz);
	vec3 Tangent0 = normalize((gWorld * vec4(Tangent, 0.0)).xyz);
	WorldPos0 = (gWorld * vec4(Position, 1.0)).xyz;

	TexCoord0 = TexCoord;
	TexCoord1 = TexCoord * gtexCount;

	vec3 bitang = normalize(cross(Normal0, Tangent0));
	NormalMatrix = mat3(
		Tangent0.x, bitang.x, Normal0.x,
		Tangent0.y, bitang.y, Normal0.y,
		Tangent0.z, bitang.z, Normal0.z
	);
}