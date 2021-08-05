#shader vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_texCoord;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
   gl_Position = projection * view * model * vec4(position.x, position.y, position.z, 1.0);
   v_texCoord = texCoord;
};

#shader fragment
#version 460 core

out vec4 FragColor;

in vec2 v_texCoord;

uniform vec4 u_color;
uniform sampler2D u_texture;

void main()
{
	vec4 texColor = texture(u_texture, v_texCoord) * u_color;
	//vec4 texColor = u_color;
	FragColor = texColor;
};