#version 330

uniform sampler2D sampler_tex;

out vec4 fragment_colour;

in vec3 varying_normal;
in vec2 varying_texcoords;

void main(void)
{
	vec3 tex_colour = texture(sampler_tex, varying_texcoords).rgb;
	tex_colour*=varying_normal.y;
	fragment_colour = vec4(tex_colour, 1.0);

	//fragment_colour = vec4(1,1,1, 1.0);
}