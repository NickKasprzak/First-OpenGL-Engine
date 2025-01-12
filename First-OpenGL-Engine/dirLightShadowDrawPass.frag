#version 330 core
out vec4 FragColor;

uniform sampler2D lightShadowMap;
uniform sampler2D positionBuffer;

uniform vec2 screenSize;
uniform mat4 LVP;

float calcShadow(vec4 fragPosLightSpace)
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
	
	// Get the shadow value for the given fragment
	float shadow = calcShadow(fragPosLightSpace);

	// If the fragment isn't in shadow, cull the
	// fragment.
	if (shadow == 0)
	{ 
		discard;
		//FragColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
		//return;
	}

	// Otherwise return the shadow's color
	FragColor = vec4(0.0f, 0.0f, 0.0f, 1.0f);
}