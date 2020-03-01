#version 330 core

layout (location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 light_pos;
uniform sampler2D curTexture;

in DATA
{
	vec4 position;
	vec4 color;
	vec2 texCoord;
} fs_in;

void main()
{
	float intensity = 1.0 / length(fs_in.position.xy - light_pos);
	// color = colour * intensity;
	color = texture(curTexture, fs_in.texCoord) * intensity;
}