#shader vertex
#version 460 core

layout(location = 0) in vec2 a_Position;
layout(location = 1) in vec2 a_TexCoords;

out vec2 v_TexCoords;

uniform mat4 u_ModelMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;

void main()
{
    v_TexCoords = a_TexCoords;
    gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_ModelMatrix * vec4(a_Position,0.0,1.0);
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
    FragColor = texColor;
};