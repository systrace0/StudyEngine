#version 460 core

in vec3 vColor;
in vec2 vTexCoords;

out vec4 FragColor;

uniform sampler2D u_texture;

void main()
{
    // Texture sampling at UV coordinates
    vec4 texColor = texture(u_texture, vTexCoords);
    
    FragColor = texColor * vec4(vColor, 1.0);
}