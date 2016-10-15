R"(
#version 330 core

layout (location = 0) out vec4 color;

in DATA {
	vec4 position;
	vec2 uv;
	vec4 color;
} fs_in;

uniform sampler2D tex;
uniform int texBits;

void main() {
	vec4 texColor;

	if(texBits == 8) {
		texColor = vec4(1, 1, 1, texture(tex, fs_in.uv).r) * fs_in.color;
	} else if(texBits == 0) {
		texColor = fs_in.color;
	} else {
		texColor = fs_in.color * texture(tex, fs_in.uv);
	}

	if(texColor.a < 0.1f) {
		discard;
	}
	color = texColor;
}
)"