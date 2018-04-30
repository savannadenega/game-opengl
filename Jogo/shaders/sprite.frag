#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D image;
uniform vec3 spriteColor;
uniform float offsetx;
uniform float offsety;

void main()
{    
   color = vec4(spriteColor, 1.0) * texture(image, vec2(TexCoords.x + offsetx, TexCoords.y + offsety));
} 