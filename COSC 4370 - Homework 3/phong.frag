
#version 330 core
out vec4 color;

in vec3 FragPos;  
in vec3 Normal;  
  
uniform vec3 lightPos; 
uniform vec3 viewPos;
uniform vec3 lightColor;
uniform vec3 objectColor;

void main()
{
    // TODO: Replace with your code...
    // If gl_Position was set correctly, this gives a totally red cube
    //color = vec4(vec3(1.f,0.f,0.f), 1.0f);

    //Getting ambient color
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    //Getting diffuse color
    vec3 norm, lightDir;
	  norm = normalize(Normal);
	  lightDir = normalize(lightPos - FragPos); //light position- fragment position 

	  float diff = max(dot(norm, lightDir), 0.0);

	  vec3 diffuse = diff * lightColor;

    //Getting specular light
    float specularStrength = 0.5;
    
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 reflectDir = reflect(-lightDir, norm);  

    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 64);
    vec3 specular = specularStrength * spec * lightColor; 



    vec3 result = (ambient + diffuse + specular) * objectColor;
    color = vec4(result, 1.0);
}