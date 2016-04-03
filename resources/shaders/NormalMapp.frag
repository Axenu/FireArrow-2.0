#version 400 core 

in vec4 pass_Position;
in vec2 pass_UV;
in vec3 pass_lightDirection;
in vec3 pass_PointLightDirection;
// in vec3 pass_ViewDirection;

out vec4 Frag_Data;

// uniform vec3 lightDirection;
uniform sampler2DArray shadowMap;
uniform mat4 inverseShadowMatrix[4];
uniform vec3 cameraPosition;

uniform sampler2D text;
uniform sampler2D bump;

void main() {
    vec3 normal = texture(bump, pass_UV).xyz * 2 - vec3(1.0);
    // normal.y *= -1;
    // normal.x *= -1;
	float ambient = 0.2;
    // vec3 pointLightPosition = vec3(9,1,0);
    //diffuse
	float light = max(dot(normalize(pass_lightDirection),normal), 0.0);
    
    //point light
    // vec3 surfaceToLight = normalize(pass_pointLight); //pointLightPosition - pass_Position.xyz
    float dista = length(pass_PointLightDirection);
    vec3 lightDirection = normalize(pass_PointLightDirection);
    float pointLightBrightness = max(dot(lightDirection,normal),0.0);

    // vec3 viewDir = normalize(pass_ViewDirection);

    // // this is blinn phong
    vec3 cameraVector = normalize(cameraPosition - pass_Position.xyz);
    vec3 halfDir = normalize(lightDirection + cameraVector);
    float specAngle = max(dot(halfDir, normal), 0.0);
    float specular = pow(specAngle, 2);
    float attenuation = 1.0 / (1.0 + pow(dista,2.0));

	int index = 0;
	if (gl_FragCoord.z/gl_FragCoord.w < 4) {
    index = 0;
    } else if (gl_FragCoord.z/gl_FragCoord.w < 12) {
        index = 1;
    } else if (gl_FragCoord.z/gl_FragCoord.w < 30) {
        index = 2;
    } else if (gl_FragCoord.z/gl_FragCoord.w < 100) {
        index = 3;
    } else {
        index = -1;
    }
    float shadow = 1.0;
    vec4 shadowCoordinateWdivide;
    float dist;
    if (index != -1) {
    	if (pass_Position.w > 0.0) {
    	shadowCoordinateWdivide = (inverseShadowMatrix[index] * pass_Position) / pass_Position.w;
        	dist = texture(shadowMap,vec3(shadowCoordinateWdivide.st, index)).r;
           if (dist > 0) {
           	if (dist < shadowCoordinateWdivide.z - 0.002)
               	shadow =  0.0;
            }
    	}
    }

	Frag_Data = vec4(1) * ((pointLightBrightness + specular) * attenuation + ambient);
	// Frag_Data = vec4(normal.xyz, 1.0);
	// Frag_Data = texture(text, pass_UV) * pointLightBrightness + specular;
    // Frag_Data = vec4(1.0);
	Frag_Data.w = 1;
}
