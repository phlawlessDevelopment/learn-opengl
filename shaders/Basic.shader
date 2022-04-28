#shader vertex
#version 460 core

layout(location = 0) in vec4 a_Position;
layout(location = 1) in vec2 a_TexCoords;
layout(location = 2) in vec4 a_Color;

out vec2 v_TexCoords;
out vec4 v_Color;
uniform mat4 u_ViewProjection;

void main()
{
    gl_Position = u_ViewProjection * a_Position;
    v_TexCoords = a_TexCoords;
    v_Color = a_Color;
};

#shader fragment
#version 460 core

layout(location = 0) out mediump vec4 color;

in vec2 v_TexCoords;
in vec4 v_Color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
    vec4 texColor = texture(u_Texture,v_TexCoords);
    color = texColor * u_Color * v_Color;
};