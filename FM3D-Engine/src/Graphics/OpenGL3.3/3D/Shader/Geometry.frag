#version 330
                                                                        
in vec2 TexCoord0;                                                                   
in vec3 WorldPos0;
in mat3 NormalMatrix;                                                                  

layout (location = 0) out vec3 WorldPosOut;   
layout (location = 1) out vec3 DiffuseOut;     
layout (location = 2) out vec3 NormalOut;     
layout (location = 3) out vec3 TexCoordOut;    
										
uniform sampler2D gColorMap;                
uniform sampler2D gNormalMap;
											
void main()									
{																
	vec4 color		= texture(gColorMap, TexCoord0);
	if(color[3] < 0.6) discard;
	DiffuseOut      = color.xyz;
	WorldPosOut     = WorldPos0;
	NormalOut		= normalize((2.0 * texture(gNormalMap, TexCoord0) - 1.0).rgb * NormalMatrix);
	TexCoordOut     = vec3(TexCoord0, 0.0);				
}
