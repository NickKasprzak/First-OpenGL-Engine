#version 330 core
out vec4 FragColor;

uniform sampler2D lightShadowMap;
uniform sampler2D positionBuffer;
uniform sampler2D normalBuffer;

uniform vec2 screenSize;
uniform mat4 LVP;
uniform vec3 lightOffset;

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
	//currentDepth = currentDepth - 0.005;

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
	vec2 texel = gl_FragCoord.xy / screenSize;

	// Convert the fragment's position to lightspace
	vec3 fragPos = vec3(texture(positionBuffer, texel));
	vec4 fragPosLightSpace = LVP * vec4(fragPos, 1.0f);

	// Get the dot product between the fragment's normal 
	// and the direction to the light to see how much they
	// point in the same direction
	vec3 fragNormal = vec3(texture(normalBuffer, texel));
	fragNormal = normalize(fragNormal);
	vec3 lightDir = normalize(lightOffset - fragPos);
	float fragToLightDot = dot(fragNormal, lightDir);
	
	// Get the shadow value for the given fragment
	float shadow = calcShadow(fragPosLightSpace, fragToLightDot);

	// If the fragment isn't in shadow, cull the
	// fragment.
	if (shadow == 0)
	{ 
		discard;
	}

	// Otherwise return the shadow's color
	FragColor = vec4(vec3(1 - shadow), 1.0f);
}