#version 450
#extension GL_ARB_separate_shader_objects : enable

// Define input vertex attributes based on Vertex::GetAttributeDescription()
// Location 0: corresponds to 'position' (vec3, VK_FORMAT_R32G32B32_SFLOAT)
layout(location = 0) in vec3 inPosition;
// Location 1: corresponds to 'color' (vec4, VK_FORMAT_R32G32B32A32_SFLOAT)
layout(location = 1) in vec4 inColor;

// Define output to the fragment shader
layout(location = 0) out vec4 fragColor;

void main() {
    // Set the clip-space position of the vertex
    gl_Position = vec4(inPosition, 1.0);
    // Pass the vertex color to the fragment shader
    fragColor = inColor;
}
