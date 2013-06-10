#version 330
out vec4 out_color;

in vec2 UV;
uniform sampler2D tex;

void main(void)
{
  out_color = texture(tex, UV);
}
