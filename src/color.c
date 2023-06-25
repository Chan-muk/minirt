/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mygo <mygo@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/21 15:29:31 by mygo              #+#    #+#             */
/*   Updated: 2023/05/21 15:29:32 by mygo             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray_primary(t_camera *cam, double u, double v)
{
	t_ray		ray;
	t_point		viewport_point;

	ray.org = cam->org;
	viewport_point = vec_add(vec_add(cam->left_bottom, \
	vec_mul(cam->right_normal, u)), vec_mul(cam->up_normal, v));
	ray.dir = unit_vec(vec_sub(viewport_point, ray.org));
	return (ray);
}

t_color	ray_color(t_scene *scene)
{
	t_vector		n;
	double			t;

	scene->rec.tmin = 0.00000001;
	scene->rec.tmax = MAXFLOAT;
	if (hit_world(scene))
		return (phong_lighting(scene));
	else
		return (scene->ambient);
}

void	color_pixels(t_mlx *mlx, t_scene *scene)
{
	int			i;
	int			j;
	t_color		pixel_color;

	j = WIN_HEIGHT - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < WIN_WIDTH)
		{
			scene->ray = ray_primary(&scene->cam, i, j);
			pixel_color = ray_color(scene);
			color_each_pixel(&mlx->img, i, (WIN_HEIGHT - 1 - j), \
			write_color(pixel_color));
			++i;
		}
		--j;
	}
}

void	color_window(t_mlx *mlx, t_scene *scene)
{
	mlx_clear_window(mlx->mlx_ptr, mlx->win_ptr);
	color_pixels(mlx, scene);
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->img.img_ptr, 0, 0);
}
