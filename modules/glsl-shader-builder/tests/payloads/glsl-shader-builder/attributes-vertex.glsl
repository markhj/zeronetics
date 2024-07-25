#version 330 core
layout (location = 0) in vec3 aPosition;
layout (location = 1) in vec3 aColor;
layout (location = 2) in vec3 aNormal;

out vec3 position;
out vec3 color;
out vec3 normal;

void main() {
    gl_Position = vec4(aPosition, 1.0);
    position = aPosition;
    color = aColor;
    normal = aNormal;
}