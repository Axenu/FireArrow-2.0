#version 400 core 

in vertexData {
    vec4 pass_Position;
    vec4 pass_Normal;
    vec4 pass_Color;
} VertexIn;

out vec4 Frag_Data;

uniform vec3 lightDirection;
uniform sampler2DArray shadowMap;
uniform mat4 inverseShadowMatrix[4];
uniform vec3 cameraPosition;

void main() {
	float ambient = 0.2;
    vec3 pointLightPosition = vec3(9,1,0);
    //diffuse
	float light = max(dot(lightDirection,VertexIn.pass_Normal.xyz), 0.0);
    
    //point light
    vec3 surfaceToLight = normalize(pointLightPosition - VertexIn.pass_Position.xyz);
    float pointLightBrightness = max(dot(surfaceToLight,VertexIn.pass_Normal.xyz),0.0);

    vec3 viewDir = normalize(cameraPosition-VertexIn.pass_Position.xyz);

    // this is blinn phong
    vec3 halfDir = normalize(surfaceToLight + viewDir);
    float specAngle = max(dot(halfDir, VertexIn.pass_Normal.xyz), 0.0);
    float specular = pow(specAngle, 80);
    float attenuation = 1.0 / (1.0 + pow(length(pointLightPosition - VertexIn.pass_Position.xyz),2.0));

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
    	if (VertexIn.pass_Position.w > 0.0) {
    	shadowCoordinateWdivide = (inverseShadowMatrix[index] * VertexIn.pass_Position) / VertexIn.pass_Position.w;
        	dist = texture(shadowMap,vec3(shadowCoordinateWdivide.st, index)).r;
           if (dist > 0) {
           	if (dist < shadowCoordinateWdivide.z - 0.0001)
               	shadow =  0.0;
            }
    	}
    }

	Frag_Data = VertexIn.pass_Color * (light * shadow + (pointLightBrightness + specular) * attenuation + ambient) ;
	// Frag_Data = pass_Position;
	// Frag_Data = dist * vec4(1.0);
    // Frag_Data = pass_Normal;
	Frag_Data.w = 1;
}
