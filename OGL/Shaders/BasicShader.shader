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
  texCor = aTexCor;
  FragPos = vec3(model * position);
  normal = mat3(transpose(inverse(model))) * aNormal;
  gl_Position = projection * view * model * position;
};  

/*------------------------------------------------------------------------------------------------------------------*/

#Shader Fragment
#version 460 core 

struct Material 
{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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

uniform vec4 u_Color; 
uniform sampler2D u_Texture; 
uniform vec3 lightPos; 
uniform vec3 viewPos; 
uniform vec3 lightColor;

void main() 
{ 
    // Ambient lighting 
    float ambientStrength = 0.1; 
    vec3 ambient = lightColor * ambientStrength;

    // Diffuse lighting 
    vec3 norm = normalize(normal);
    vec3 lightDir = normalize(lightPos - FragPos); 
    float diff = max(dot(norm, lightDir), 0.0); 
    vec3 diffuse = lightColor * (diff * lightColor);

    // Specular lighting 
    float specularStrength = 0.5;
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256.0);
    vec3 specular = lightColor * (spec * specularStrength);

    // Combine all lighting components 
    vec3 lighting = ambient + diffuse + specular; 

    // Sample texture color 
    vec4 texColor = texture(u_Texture, texCor); 

    // Combine texture color with lighting
    vec3 result = lighting * vec3(texColor);// * vec3(u_Color);

    // Final color output 
    FragColor = vec4(result, 1.0);
};
			 			