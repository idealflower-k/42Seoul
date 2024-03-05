#include "minirt_bonus.h"
#include "defs_bonus.h"
#include "utils_bonus.h"

int	destroy(t_meta *meta)
{
	objs_clear(&meta->objs, free);
	ft_lstclear(&meta->spot_lights, free);
	mlx_destroy_image(meta->mlx_assets.mlx, meta->mlx_assets.img.img);
	mlx_destroy_window(meta->mlx_assets.mlx, meta->mlx_assets.win);
	mlx_del(meta->mlx_assets.mlx);
	free(meta->thd_pool.rendrer);
	free(meta->thd_pool.tids);
	free(meta);
	exit(EXIT_SUCCESS);
}
