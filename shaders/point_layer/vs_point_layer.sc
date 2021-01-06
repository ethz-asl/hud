$input a_position, a_texcoord0, i_data0
$output v_texcoord0

void main() {
  vec2 position_xy = a_position.xy + i_data0;
  vec3 position_xyz = vec3(position_xy, a_position.z);
	gl_Position = vec4(position_xyz, 1.0);
	v_texcoord0 = a_texcoord0;
}
