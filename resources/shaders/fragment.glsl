#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 FragNormal;

uniform sampler2D texture0;
uniform vec4 ambientColor;
uniform vec3 diffuseDir;
uniform vec4 diffuseColor;

void main() {
  FragColor = texture(texture0, TexCoord) * (ambientColor + diffuseColor * max(0, dot(-normalize(diffuseDir), FragNormal)));
}
