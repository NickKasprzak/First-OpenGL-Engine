#version 330 core
out vec4 FragColor;

// Directional light uniforms
uniform vec3 ambientColor;
uniform vec3 diffuseColor;
uniform vec3 specularColor;
uniform vec3 lightDirection;
uniform vec3 viewPosition;

// GBuffer uniforms
uniform sampler2D GB_Position;
uniform sampler2D GB_Diffuse;
uniform sampler2D GB_UV;
uniform sampler2D GB_Normal;

uniform vec2 screenSize;

vec4 calcDirectionalLight(vec3 normal, vec3 viewDir)
{
	vec3 lightDir = normalize(-lightDirection);
	float diffuseFactor = max(dot(normal, lightDir), 0.0f); 

	vec3 reflectDir = reflect(-lightDir, normal);
	float specularFactor = dot(viewDir, reflectDir);
	specularFactor = pow(max(specularFactor, 0.0f), 32); // shininess

	vec3 ambientLight = ambientColor;
	vec3 diffuseLight = diffuseColor * diffuseFactor;
	vec3 specularLight = specularColor * specularFactor;
	
	return vec4(ambientLight + diffuseLight + specularLight, 1.0f);
}

void main()
{
	vec2 fragScreenPos = gl_FragCoord.xy / screenSize;

	vec3 fragPos = vec3(texture(GB_Position, fragScreenPos));
	vec3 fragColor = vec3(texture(GB_Diffuse, fragScreenPos));
	vec3 fragNormal = vec3(texture(GB_Normal, fragScreenPos));
	fragNormal = normalize(fragNormal);

	vec3 viewDir = normalize(viewPosition - fragPos);

	FragColor = vec4(fragColor, 1.0f) * calcDirectionalLight(fragNormal, viewDir);
}