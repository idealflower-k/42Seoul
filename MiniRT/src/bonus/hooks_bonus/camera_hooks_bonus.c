#include "minirt_bonus.h"
#include "defs_bonus.h"

static inline void	_update_camera_forward(
	t_camera *camera, const double yaw, const double pitch)
{
	const double	pitch_rad = degree_to_radian(pitch);
	const double	yaw_rad = degree_to_radian(yaw);
	const t_vec3	vec3 = vec3_init(cos(yaw_rad) * cos(pitch_rad),
			sin(pitch_rad),
			sin(yaw_rad) * cos(pitch_rad));

	camera->forward = vec3;
}

void	camera_mouse_hooks(const int pos[2], t_meta *meta)
{
	const double	camera_speed = 0.05;

	meta->camera.yaw -= (pos[X] - meta->hooks.prev_pos[X]) * camera_speed;
	meta->camera.pitch -= (pos[Y] - meta->hooks.prev_pos[Y]) * camera_speed;
	if (meta->camera.yaw < 0.0f)
		meta->camera.yaw += 180.0f;
	if (meta->camera.yaw > 360.0f)
		meta->camera.yaw -= 180.0f;
	if (meta->camera.pitch > 89.0f)
		meta->camera.pitch = 45.0f;
	if (meta->camera.pitch < -89.0f)
		meta->camera.pitch = -45.0f;
	_update_camera_forward(&meta->camera, meta->camera.yaw, meta->camera.pitch);
	meta->hooks.prev_pos[X] = pos[X];
	meta->hooks.prev_pos[Y] = pos[Y];
}

void	camera_key_hooks(const int keydata, t_meta *meta)
{
	const double	camera_speed = 0.10;

	if (keydata == MLX_KEY_W)
		meta->camera.pos = vec3_minus(meta->camera.pos,
				vec3_scalar_multi(meta->camera.forward, camera_speed));
	if (keydata == MLX_KEY_S)
		meta->camera.pos = vec3_plus(meta->camera.pos,
				vec3_scalar_multi(meta->camera.forward, camera_speed));
	if (keydata == MLX_KEY_D)
		meta->camera.pos = vec3_plus(meta->camera.pos,
				vec3_scalar_multi(meta->camera.right, camera_speed));
	if (keydata == MLX_KEY_A)
		meta->camera.pos = vec3_minus(meta->camera.pos,
				vec3_scalar_multi(meta->camera.right, camera_speed));
	if (keydata == MLX_KEY_E)
		meta->camera.pos = vec3_minus(meta->camera.pos,
				vec3_scalar_multi(meta->camera.up, camera_speed));
	if (keydata == MLX_KEY_Q)
		meta->camera.pos = vec3_plus(meta->camera.pos,
				vec3_scalar_multi(meta->camera.up, camera_speed));
}
