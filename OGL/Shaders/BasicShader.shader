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
  gl_Position = projection * view * vec4(FragPos, 1.0);
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

struct DirectionalLight
{
	vec4 direction;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
};

struct PointLight
{
    vec4 position;
    vec4 ambient;
    vec4 diffuse;
	vec4 specular;
	float constant;
	float linear;
	float quadratic;
};

struct SpotLight
{
	vec4 position;
	vec4 direction;
	vec4 ambient;
	vec4 diffuse;
	vec4 specular;
	float constant;
	float linear;
	float quadratic;
	float cutOff;
	float outerCutOff;
};

#define NR_POINT_LIGHTS 1

uniform DirectionalLight directionalLight;
uniform PointLight pointLight[NR_POINT_LIGHTS];
uniform SpotLight spotLight;

uniform Light light;  
uniform Material material;

in vec4 vertexColor; 
in vec2 texCor; 
in vec3 normal; 
in vec3 FragPos; 

out vec4 FragColor; 

uniform vec3 objectColor;
uniform vec3 lightPos; 
uniform vec3 viewPosition; 
uniform vec3 lightColor;

vec4 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir);
vec4 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);
vec4 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir);


void main() 
{ 

	vec3 norm = normalize(normal); 
	vec3 viewDir = normalize(viewPosition - FragPos);

	// Calculate the result of each light type 
	vec4 result = CalculateDirectionalLight(directionalLight, norm, viewDir); 

	for (int i = 0; i < NR_POINT_LIGHTS; i++) 
	{ 
		vec4 pointLightResult = CalculatePointLight(pointLight[i], norm, FragPos, viewDir);
		if(pointLightResult == vec4(0.0, 0.0, 0.0, 1.0))
		{
			result = vec4(1.0, 0.0, 0.0, 1.0);
		} else {
			result += pointLightResult;
		}
	} 
	result += CalculateSpotLight(spotLight, norm, FragPos, viewDir);

	//FragColor = vec4(lightDir * 0.5 + 0.5, 1.0); // visualize light direction
	//FragColor = vec4(normal * 0.5 + 0.5, 1.0); // visualize normals

    FragColor = result;
};

vec4 CalculateDirectionalLight(DirectionalLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(light.direction.xyz);
	


    //Diffuse
	float diff = max(dot(normal, lightDir), 0.0);
	vec3 diffuse = light.diffuse.xyz * diff * texture(material.texture_diffuse, texCor).rgb;

    //Ambient
	vec3 ambient = light.ambient.xyz * texture(material.texture_diffuse, texCor).rgb;

	//Specular
	vec3 reflectDir = normalize(reflect(-lightDir, normal));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
    vec3 specular = light.specular.xyz * spec * texture(material.texture_specular, texCor).rgb;
	
	return vec4(ambient + diffuse + specular, 1.0);
	
};

vec4 CalculatePointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir) 
{ 
	vec3 lightDir = normalize(light.position.xyz - fragPos); 
	float distance = length(light.position.xyz - fragPos);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance)); 
	// Ambient 
	vec3 ambient = light.ambient.xyz * texture(material.texture_diffuse, texCor).rgb;
	// Diffuse 
	float diff = max(dot(normal, lightDir), 0.0); 
	vec3 diffuse = light.diffuse.xyz * diff * texture(material.texture_diffuse, texCor).rgb;
	// Specular 
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); 
	vec3 specular = light.specular.xyz * spec * texture(material.texture_specular, texCor).rgb;
	// Apply attenuation 
	ambient *= attenuation; 
	diffuse *= attenuation; 
	specular *= attenuation; 
	return vec4(ambient + diffuse + specular, 0.0);
};

vec4 CalculateSpotLight(SpotLight light, vec3 normal, vec3 fragPos, vec3 viewDir) 
{ 
	vec3 lightDir = normalize(light.position.xyz - fragPos);
	float theta = dot(lightDir, normalize(light.direction.xyz));
	float epsilon = light.cutOff - light.outerCutOff; 
	float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0); 
	float distance = length(light.position.xyz - fragPos); 
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));
	
	// Ambient 
	vec3 ambient = light.ambient.xyz * texture(material.texture_diffuse, texCor).rgb;
	// Diffuse 
	float diff = max(dot(normal, lightDir), 0.0); 
	vec3 diffuse = light.diffuse.xyz * diff * texture(material.texture_diffuse, texCor).rgb;
	// Specular 
	vec3 reflectDir = reflect(-lightDir, normal);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess); 
	vec3 specular = light.specular.xyz * spec * texture(material.texture_specular, texCor).rgb;

	ambient *= attenuation * intensity; 
	diffuse *= attenuation * intensity; 
	specular *= attenuation * intensity; 

	return vec4(ambient + diffuse + specular, 1.0);
};

			 			