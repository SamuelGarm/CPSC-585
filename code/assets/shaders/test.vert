#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;

uniform mat4 M;
uniform mat4 V;
uniform mat4 P;

out vec3 fragColor;

void main() {
	fragColor = vertCol;
	gl_Position = P * V * M * vec4(vertPos, 1.0);
}
