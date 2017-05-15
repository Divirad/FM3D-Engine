#version 330

in vec2 TexCoord0;
in vec2 TexCoord1;
in vec3 WorldPos0;
in mat3 NormalMatrix;

layout (location = 0) out vec3 WorldPosOut;
layout (location = 1) out vec4 ColorOut;
layout (location = 2) out vec3 NormalOut;

uniform sampler2D gColorMap0;
uniform sampler2D gColorMap1;
uniform sampler2D gColorMap2;

uniform sampler2D gSpatMap;
uniform sampler2D gNormalMap;

uniform float gSpecularFactor0;
uniform float gSpecularFactor1;
uniform float gSpecularFactor2;

void main()
{
	vec3 blend = texture(gSpatMap, TexCoord0).rgb;
	blend = normalize(blend);
	vec4 color = (blend.r * texture(gColorMap0, TexCoord1)) + (blend.g * texture(gColorMap1, TexCoord1)) + (blend.b * texture(gColorMap2, TexCoord1));
	

	if(color[3] < 0.6) discard;
	ColorOut	= vec4(color.rgb, (blend.r * gSpecularFactor0) + (blend.g * gSpecularFactor1) + (blend.b * gSpecularFactor2));
	WorldPosOut = WorldPos0;
	NormalOut	= normalize((2.0 * texture(gNormalMap, TexCoord0) - 1.0).rgb * NormalMatrix);
}
