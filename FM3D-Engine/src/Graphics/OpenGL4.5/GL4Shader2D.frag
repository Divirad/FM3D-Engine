R"(
#version 330 core

layout (location = 0) out vec4 color;

in DATA {
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
} fs_in;

uniform sampler2D tex[32];
uniform int texBits[32];

void main() {
	int tid = int(fs_in.tid - 0.5);
	vec4 texColor;

	if(texBits[tid] == 8) {
		texColor = vec4(1, 1, 1, texture(tex[tid], fs_in.uv).r) * fs_in.color;
	} else if(texBits[tid] == 0) {
		texColor = fs_in.color;
	} else {
		texColor = fs_in.color * texture(tex[tid], fs_in.uv);
	}

	if(texColor.a < 0.1f) {
		discard;
	}
	color = texColor;
}
)"