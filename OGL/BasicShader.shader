#Shader Vertex
#version 460 core

layout(location = 0)in vec4 position;
layout(location = 1)in vec4 aColor;
layout(location = 2)in vec2 aTexCor;

out vec4 vertexColor;
out vec2 texCor;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


void main()                
{
  gl_Position = projection * view * model * position;
  vertexColor = aColor;
  texCor = aTexCor;
};  

/*------------------------------------------------------------------------------------------------------------------*/

#Shader Fragment
#version 460 core

in vec4 vertexColor;
in vec2 texCor;

out vec4 tex;  

uniform vec4 u_Color;
uniform sampler2D u_Texture;


void main()                
{      
	tex = texture(u_Texture, texCor) * u_Color;
};				 			