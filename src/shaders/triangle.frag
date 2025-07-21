#version 450
#extension GL_ARB_separate_shader_objects : enable

// Input from the vertex shader.
// Location MUST match the 'out' location in the vertex shader.
layout(location = 0) in vec4 fragColor;

// Output to the framebuffer.
layout(location = 0) out vec4 outColor;

void main() {
}
