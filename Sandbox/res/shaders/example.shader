
-- vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoords;

out VS_OUT {
    vec2 texCoords;
} vs_out;

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;

void main() {
    
    vs_out.texCoords = aTexCoords;
    gl_Position = uProjectionMatrix * uViewMatrix * vec4(aPos, 1.0);
    
}

-- fragment
#version 330 core

out vec4 FragColor;

in VS_OUT{
    vec2 texCoords;
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