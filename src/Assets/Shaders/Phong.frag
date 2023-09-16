#version 460 core

in vec3 normal;
in vec4 fragPos;

out vec4 FragColor;

void main()
{
    vec3 objectColor = vec3(0.8f, 0.0f, 0.5f);
    vec3 lightColor = vec3(1.0f);

    vec3 lightDirection = normalize(vec3(1.0f) - fragPos.xyz);
    vec3 normal = normalize(normal);
    float diffuseIntensity = max(dot(lightDirection, normal), 0.0f);
    vec3 diffuseColor = lightColor * diffuseIntensity;

    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = (ambient + diffuseColor) * objectColor;
    FragColor = vec4(result, 1.0);
}
