#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
layout (location = 2) in float aPeso;

out vec3 vertexColor;

uniform float xOffset;
uniform float yOffset;
uniform float escala;
uniform float viento;
uniform float aspecto;

void main()
{
    vec2 p = vec2(aPos.x + viento * aPeso, aPos.y) * escala;
    gl_Position = vec4((p.x + xOffset) / aspecto, p.y + yOffset, aPos.z, 1.0);
    vertexColor = aColor;
}
