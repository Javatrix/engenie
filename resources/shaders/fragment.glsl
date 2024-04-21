#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 FragNormal;

uniform sampler2D texture0;

void main() {
  FragColor = texture(texture0, TexCoord) * vec4(FragNormal, 1);
}
