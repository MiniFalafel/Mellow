
-- vertex
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out VS_OUT {
    vec3 color;
} vs_out;

void main() {
    
    vs_out.color = aColor;
    gl_Position = vec4(aPos, 1.0);
    
}

-- geometry
#version 330 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 15) out;

in VS_OUT {
    vec3 color;
} gs_in[];

out vec3 fragColor;

uniform float uTime;

float rand(vec2 co) {
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

float randf(float c) {
    return fract(sin(c) * 43758.5453);
}

void GenerateShape(int index) {

    fragColor = gs_in[index].color;
    float tRand = rand(gl_in[index].gl_Position.xy + vec2(sin(uTime), 0.0));
    vec2 randVec = vec2(randf(tRand), tRand);
    for (int i = 0; i < 5; i++) {
        gl_Position = gl_in[index].gl_Position + vec4(0.5 * randVec, 0.0, 0.0);
        EmitVertex();
        float tRand = rand(randVec);
        randVec = vec2(randf(tRand), tRand);
    }

    EndPrimitive();
}

void main() {

    GenerateShape(0);
    GenerateShape(1);
    GenerateShape(2);

}

-- fragment
#version 330 core

out vec4 FragColor;

in vec3 fragColor;

uniform vec3 uColor;

void main() {
    
    FragColor = vec4(uColor * fragColor, 1.0);
    
}