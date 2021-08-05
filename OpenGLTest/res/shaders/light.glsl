#shader vertex
#version 460 core

layout(location = 0) in vec4 position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection * view * model * vec4(position.x, position.y, position.z, 1.0);
};

#shader fragment
#version 460 core

out vec4 FragColor;

uniform vec3 viewPos;

void main()
{
	vec3 pos = viewPos;
	FragColor = vec4(1.0);
};