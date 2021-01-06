$input v_texcoord0
$output a_color0

#include "./bgfx_shader.sh"

void main() {
	float radius = 1.0; // In local coordinates.
	float distance = sqrt(dot(v_texcoord0, v_texcoord0));
	if (distance > radius) {
		discard;
	}
	gl_FragColor = vec4(1.0, 0.5, 0.5, 1.0);
}
