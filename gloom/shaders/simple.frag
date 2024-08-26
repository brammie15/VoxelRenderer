#version 460 core
precision highp float;

out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;
in vec3 pos;

uniform sampler2D ourTexture;

void main()
{
    FragColor = texture(ourTexture, TexCoord);
//    FragColor = vec4(1.0f, TexCoord.x, 1.0f, 1.0);
//    FragColor = vec4(137 / 255, 85 / 255, 95 / 255, 1.0f);
}