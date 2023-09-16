#version 460 core

in vec3 normal;
in vec4 fragPos;

out vec4 FragColor;

uniform vec3 lightPos;
uniform vec3 cameraPos;

void main()
{
    vec3 objectColor = vec3(0.8f, 0.0f, 0.5f);
    vec3 lightColor = vec3(1.0f);

    vec3 lightDirection = normalize(lightPos - fragPos.xyz);
    vec3 normal = normalize(normal);

    float diffuseIntensity = max(dot(lightDirection, normal), 0.0f);
    vec3 diffuseColor = lightColor * diffuseIntensity;

    vec3 viewDirection = normalize(cameraPos - fragPos.xyz);
    vec3 reflectDirection = reflect(-lightDirection, normal);

    float specularIntensity = pow(max(dot(viewDirection, reflectDirection), 0.0), 128);
    vec3 specularColor = 0.5f * specularIntensity * lightColor;

    float ambientStrength = 0.1f;
    vec3 ambientColor = ambientStrength * lightColor;

    vec3 result = (ambientColor + diffuseColor + specularColor) * objectColor;
    FragColor = vec4(result, 1.0);
}
