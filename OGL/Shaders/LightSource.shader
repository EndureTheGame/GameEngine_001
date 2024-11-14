#Shader Vertex
#version 460 core

layout(location = 0)in vec4  position;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	  gl_Position = projection * view * model * position;
};

/*------------------------------------------------------------------------------------------------------------------*/

#Shader Fragment
#version 460 core

uniform vec3 color;

out vec4 FragColor;

void main()
{
    FragColor = vec4(color, 1.0); // set all 4 vector values to 1.0
};