#shader vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 aNormal;

out vec3 FragPosition;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection * view * model * vec4(position.x, position.y, position.z, 1.0);
   FragPosition = vec3(model * position);
   // Should be calculated on cpu side since its costly here
   Normal = mat3(transpose(inverse(model))) * aNormal;
};

#shader fragment
#version 460 core

out vec4 FragColor;

in vec3 FragPosition;
in vec3 Normal;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	vec3 normal = normalize(Normal);
	vec3 lightDir = normalize(lightPos - FragPosition);

	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	float specularStrength = 0.5;

	vec3 viewDir = normalize(viewPos - FragPosition);
	vec3 reflectDir = reflect(-lightDir, normal);

	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
	vec3 specular = specularStrength * spec * lightColor;

	vec4 color = vec4((ambient + diffuse + specular) * objectColor, 1.0);
	FragColor = color;
};