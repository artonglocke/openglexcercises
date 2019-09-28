#version 330 core

out vec4 color;

in vec2 v_TexCoords;

uniform sampler2D uTexture;

void main()
{
	vec4 textureColor = texture2D(uTexture, v_TexCoords);
	color = textureColor;
}