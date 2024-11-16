#Shader Vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec4 aColor;
layout(location = 2) in vec2 aTexCor;
layout(location = 3) in vec3 aNormal;

out vec4 vertexColor;
out vec2 texCor;
out vec3 normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()                
{
  vertexColor = aColor;
  FragPos = vec3(model * position);
  normal = mat3(transpose(inverse(model))) * aNormal;
  texCor = aTexCor;
  gl_Position = projection * view * model * position;
};  

/*------------------------------------------------------------------------------------------------------------------*/

#Shader Fragment
#version 460 core 

struct Material 
{
	sampler2D texture_diffuse;
    sampler2D texture_specular;
   // vec3 specular;
    float shininess;
}; 

struct Light 
{
    vec3 position;
  
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

uniform Light light;  
uniform Material material;

in vec4 vertexColor; 
in vec2 texCor; 
in vec3 normal; 
in vec3 FragPos; 

out vec4 FragColor; 


uniform vec3 lightPos; 
uniform vec3 viewPosition; 
uniform vec3 lightColor;

void main() 
{ 
    /*------------------------------------------------------------------------------------------------------------------*/
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(light.position - FragPos);

    // Ambient lighting 
    vec3 ambient = light.ambient * vec3(texture(material.texture_diffuse, texCor)).rgb;

    /*------------------------------------------------------------------------------------------------------------------*/

    // Diffuse lighting 
    float diff = max(dot(norm, lightDir), 0.0); 
    vec3 diffuse = light.diffuse * (diff * vec3(texture(material.texture_diffuse, texCor))).rgb;

     /*------------------------------------------------------------------------------------------------------------------*/

    // Specular lighting 
    vec3 viewDir = normalize(viewPosition - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular * (spec * vec3(texture(material.texture_specular, texCor))).rgb;

     /*------------------------------------------------------------------------------------------------------------------*/

    // Combine all lighting components 
    vec3 result = ambient + diffuse + specular; 

    // Final color output 
    FragColor = vec4(result, 1.0);
};
			 			