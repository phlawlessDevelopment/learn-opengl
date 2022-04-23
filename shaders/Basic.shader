#shader vertex
#version 460 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoords;

out vec2 v_TexCoords;

void main()
{
    gl_Position = position;
    v_TexCoords = texCoords;
};

#shader fragment
#version 460 core

layout(location = 0) out mediump vec4 color;

in vec2 v_TexCoords;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture,v_TexCoords);
    color = texColor; 
};