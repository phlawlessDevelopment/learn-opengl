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
    v_TexCoords = a_TexCoords;
    v_Color = a_Color;
    gl_Position = u_ViewProjection * a_Position;
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
    // FragColor =  v_Color;
    FragColor = texColor * v_Color;
};