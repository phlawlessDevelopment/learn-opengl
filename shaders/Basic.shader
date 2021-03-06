#shader vertex
#version 460 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TexCoords;

out vec2 v_TexCoords;

uniform mat4 u_MVPMatrix;

void main()
{
    v_TexCoords = a_TexCoords;
    gl_Position = u_MVPMatrix * a_Position;
};

#shader fragment
#version 460 core

out vec4 FragColor;

in vec2 v_TexCoords;
in vec4 v_Color;

uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture,v_TexCoords);
    FragColor = texColor;
};