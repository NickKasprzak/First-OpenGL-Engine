#version 330 core
out vec4 FragColor;

// Directional light uniforms
uniform vec3 lightColor;
uniform vec3 lightDirection;
uniform sampler2D lightShadowMap;
uniform mat4 lightSpaceTransform;
uniform vec3 lightOffset;

// GBuffer uniforms
uniform sampler2D GB_Position;
uniform sampler2D GB_Diffuse;
uniform sampler2D GB_UV;
uniform sampler2D GB_Normal;

uniform vec3 viewPosition;
uniform vec2 screenSize;

vec3 calcDirectionalLight(vec3 normal, vec3 viewDir)
{
	// Calculate how much light is hitting the surface
	vec3 lightDir = normalize(-lightDirection);
	float diffuseFactor = max(dot(normal, lightDir), 0.0f); 

	// Calculate how much light is being reflected off the surface
	vec3 reflectDir = reflect(-lightDir, normal);
	float specularFactor = dot(viewDir, reflectDir);
	specularFactor = pow(max(specularFactor, 0.0f), 32); // shininess

	// Calculate final light color
	vec3 ambientLight = lightColor;
	vec3 diffuseLight = lightColor * diffuseFactor;
	vec3 specularLight = vec3(1.0f) * specularFactor;
	
	return diffuseLight + specularLight;
}

float calcShadow(vec4 fragPosLightSpace, float fragLightDot)
{
	// Perspective divide to NDC using the w coordinate
	// supplied to the fragPos from the LVP.
	//
	// (Only really needed for perspective LVPs to undo the warp
	//  caused by perspective view matrices).
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;

	// Convert the NDC coordinates from the -1 to 1 range
	// to the 0 to 1 range so they can sample depth values.
	projCoords = projCoords * 0.5 + 0.5;

	// Get the depth of the surface closest to the light
	// for the given fragment
	float closestDepth = texture(lightShadowMap, projCoords.xy).r;

	// Get the depth of the current position our fragment
	// references, just being its distance on the z axis
	// from the light in light space.
	float currentDepth = projCoords.z;

	// Calculate a bias that scales based on how steep the
	// surface of the fragment is relative to the light based
	// on their resulting dot product to smooth out the current
	// depth.
	float bias = max(0.05 * (1.0 - fragLightDot), 0.005);
	currentDepth = currentDepth - bias;

	// If the closest depth is higher than the current 
	// depth, something is blocking light from hitting
	// the fragment's position and is considered in
	// shadow.
	if (currentDepth > closestDepth)
	{
		return 1;
	}

	// Otherwise, the fragment is being hit by light
	return 0;
}


void main()
{
	vec2 texPos = gl_FragCoord.xy / screenSize;

	// Geometry data
	vec3 fragPos = vec3(texture(GB_Position, texPos));
	vec3 fragColor = vec3(texture(GB_Diffuse, texPos));
	vec3 fragNormal = vec3(texture(GB_Normal, texPos));
	fragNormal = normalize(fragNormal);
	vec4 fragPosLightSpace = lightSpaceTransform * vec4(fragPos, 1.0f);

	vec3 viewDir = normalize(viewPosition - fragPos);

	// Surface and light direction alignment
	vec3 lightOffsetDir = normalize(lightOffset - fragPos);
	float fragToLightDot = dot(fragNormal, lightOffsetDir);

	vec3 DSColor = calcDirectionalLight(fragNormal, viewDir);
	float shadow = calcShadow(fragPosLightSpace, fragToLightDot);

	vec3 finalColor = fragColor * (lightColor + (DSColor * (1 - shadow)));
	FragColor = vec4(finalColor, 1.0f);
}