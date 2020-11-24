$input v_texcoord0
$output a_color0

#include "./bgfx_shader.sh"

SAMPLER2D(textureColor, 0);

void main() {
	vec4 color = texture2D(textureColor, v_texcoord0);
	gl_FragColor = color;
}
