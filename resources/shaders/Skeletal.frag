#version 400 core 

in vec4 pass_Position;
in vec4 pass_Normal;
in vec4 pass_Color;

out vec4 Frag_Data;

uniform vec3 lightDirection;
uniform sampler2DArray shadowMap;
uniform mat4 inverseShadowMatrix[4];

void main() {
	float ambient = 0.2;
	vec4 light = max(dot(lightDirection,pass_Normal.xyz), 0.0) * vec4(1,1,1,1);

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

	Frag_Data = pass_Color * (light * shadow + ambient);
	// Frag_Data = pass_Position;
	// Frag_Data = dist * vec4(1.0);
	Frag_Data.w = 1;
}
