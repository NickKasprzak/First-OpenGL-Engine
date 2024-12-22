#version 330 core
out vec4 FragColor;

// Point light uniforms
uniform vec3 lightPosition;
uniform vec3 lightColor;
uniform float radius;
uniform float intensity;

// GBuffer uniforms
uniform sampler2D GB_Position;
uniform sampler2D GB_Diffuse;
uniform sampler2D GB_UV;
uniform sampler2D GB_Normal;

uniform vec3 viewPosition;
uniform vec2 screenSize;

vec4 calcPointLight(vec3 fragPos, vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(lightPosition - fragPos);
	float diffuseFactor = max(dot(normal, lightDir), 0.0f); 

	vec3 reflectDir = reflect(-lightDir, normal);
	float specularFactor = dot(viewDir, reflectDir);
	specularFactor = pow(max(specularFactor, 0.0f), 32); // shininess

	float dist = length(lightPosition - fragPos);
	float attenuation = max(intensity / sqrt(dist) - intensity / sqrt(radius), 0); // Epic's attenuation formula
	
	vec3 ambientLight = lightColor;
	ambientLight *= attenuation;
	vec3 diffuseLight = lightColor * diffuseFactor;
	diffuseLight *= attenuation;
	vec3 specularLight = vec3(1.0f) * specularFactor;
	specularLight *= attenuation;

	return vec4(ambientLight + diffuseLight + specularLight, 1.0f);
}

void main()
{
	vec2 texPos = gl_FragCoord.xy / screenSize;

	vec3 fragPos = vec3(texture(GB_Position, texPos));
	vec3 fragColor = vec3(texture(GB_Diffuse, texPos));
	vec3 fragNormal = vec3(texture(GB_Normal, texPos));
	fragNormal = normalize(fragNormal);

	vec3 viewDir = normalize(viewPosition - fragPos);

	FragColor = vec4(fragColor, 1.0f) * calcPointLight(fragPos, fragNormal, viewDir);
}