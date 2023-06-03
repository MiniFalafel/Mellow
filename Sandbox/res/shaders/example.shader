
-- vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 2) in vec2 aTexCoords;

out VS_OUT {
    vec2 texCoords;
    vec3 FragCoords;
} vs_out;

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;

void main() {
    
    vs_out.texCoords = aTexCoords;
    vs_out.FragCoords = vec3(uModelMatrix * vec4(aPos, 1.0));
    gl_Position = uProjectionMatrix * uViewMatrix * vec4(vs_out.FragCoords, 1.0);
    
}

-- fragment
#version 330 core

out vec4 FragColor;

in VS_OUT{
    vec2 texCoords;
    vec3 FragCoords;
} fs_in;

uniform vec4 uColor;
uniform sampler2D uTexImage;

void main() {
    
    vec4 color = texture(uTexImage, fs_in.texCoords).rgba;

    if (color.a * uColor.a == 0.0) { // If either color is zero
        discard;
    }

    FragColor = color * uColor;
    
}