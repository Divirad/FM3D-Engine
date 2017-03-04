#version 330

in vec2 TexCoord0;
in vec3 WorldPos0;
#if Normalmap
in mat3 NormalMatrix;
#else
in vec3 Normal0;
#end

layout (location = 0) out vec3 WorldPosOut;
layout (location = 1) out vec4 ColorOut;
layout (location = 2) out vec3 NormalOut;

uniform sampler2D gColorMap;
#if Normalmap
uniform sampler2D gNormalMap;
#end
#if Specularmap
uniform sampler2D gSpecularMap;
#end
uniform float gSpecularFactor;

void main()
{
	vec4 color	= texture(gColorMap, TexCoord0);
	if(color[3] < 0.6) discard;
#if Specularmap
	ColorOut	= vec4(color.rgb, gSpecularFactor * texture(gSpecularMap, TexCoord0).r);
#else
	ColorOut	= vec4(color.rgb, gSpecularFactor);
#end
	WorldPosOut = WorldPos0;
#if Normalmap
	NormalOut	= normalize((2.0 * texture(gNormalMap, TexCoord0) - 1.0).rgb * NormalMatrix);
#else
	NormalOut	= normalize(Normal0);
#end	
}
