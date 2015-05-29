#version 400 core

uniform mat4 MVPMatrix;

layout(location = 0) in vec3 in_Position;
layout(location = 1) in vec3 in_Normal;
layout(location = 2) in vec3 in_Color;

out vec4 pass_Normal;
out vec4 pass_Color;

void main() {
    pass_Normal = normalize(vec4(in_Normal, 1.0));
    pass_Color = vec4(in_Color, 1.0);
    gl_Position = MVPMatrix * vec4(in_Position.x, in_Position.y, in_Position.z, 1.0);
}