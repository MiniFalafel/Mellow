
-- vertex
#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoords;

out VS_OUT{
    vec2 texCoords;
    vec3 FragPos;
    vec3 Normal;
} vs_out;

uniform mat4 uProjectionMatrix;
uniform mat4 uViewMatrix;
uniform mat4 uModelMatrix;
uniform float uTime;

void main() {

    vs_out.texCoords = aTexCoords;
    vs_out.FragPos = vec3(uModelMatrix * vec4(aPos, 1.0));
    vs_out.FragPos.z += sin(uTime);
    vs_out.Normal = mat3(transpose(inverse(uModelMatrix))) * aNormal;
    gl_Position = uProjectionMatrix * uViewMatrix * vec4(vs_out.FragPos, 1.0);

}

-- fragment
#version 330 core

out vec4 FragColor;

in VS_OUT{
    vec2 texCoords;
    vec3 FragPos;
    vec3 Normal;
} fs_in;

uniform vec4 uColor;
uniform sampler2D uTexImage;

uniform vec3 uLightPos;
uniform vec3 uLightColor;

uniform vec3 uCameraPos;

void main() {

    vec4 color = texture(uTexImage, fs_in.texCoords).rgba;

    if (color.a * uColor.a == 0.0) { // If either color is zero
        discard;
    }

    // LIGHTING
    vec3 lightDir = normalize(fs_in.FragPos - uLightPos);

    // diffuse
    vec3 norm = normalize(fs_in.Normal);
    float diffuse = max(dot(norm, -lightDir), 0.0);

    // specular
    vec3 viewDir = normalize(fs_in.FragPos - uCameraPos);
    float specular = pow(max(dot(-viewDir, reflect(lightDir, norm)), 0.0), 256.0);

    // attenuation
    float attenuation = 1.0 / pow(length(fs_in.FragPos - uLightPos), 2.0);

    vec3 lum = vec3(diffuse + specular) * uLightColor * attenuation;

    FragColor = color * uColor * vec4(lum, 1.0);

}