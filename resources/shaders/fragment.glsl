#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec2 TexCoord;
in vec3 FragNormal;

uniform sampler2D texture0;
uniform float ambientStrength;
uniform vec3 diffuseDir;
uniform vec4 diffuseColor;
uniform vec3 viewPos;
uniform float specularity;
uniform float shininess;

void main() {
  vec4 ambientLight = vec4(ambientStrength, ambientStrength, ambientStrength, 1);
  vec4 diffuseLight = diffuseColor * max(0, dot(normalize(diffuseDir), FragNormal));
  vec3 viewDir = normalize(viewPos - FragPos);
  vec3 reflectionDir = reflect(-diffuseDir, FragNormal);
  vec4 specularLight = specularity * pow(max(dot(viewDir, reflectionDir), 0.0), shininess) * diffuseColor;
  FragColor = texture(texture0, TexCoord) * (ambientLight + diffuseLight + specularLight);
}
