#version 330
out vec4 out_color;

in vec3 UV;
uniform sampler2D tex;

void main(void)
{
    out_color = texture(tex, vec2(UV.x, UV.y));
}
