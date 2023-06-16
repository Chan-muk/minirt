/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/23 12:04:41 by chajung           #+#    #+#             */
/*   Updated: 2023/04/23 12:04:42 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_canvas	canvas(int x, int y)
{
	t_canvas	canvas;

	canvas.width = x;
	canvas.height = y;
	canvas.aspect_ratio = x / y;
	return (canvas);
}

void	set_lights(t_hit_array *light)
{
	light[0].type = _light;
	light[0].center = new_vec(0, 5, 0);
	light[0].color = new_color(1, 1, 1);
	light[0].light_color = new_color(1, 1, 1);
	light[0].bright_ratio = 0.5;

	light[1].type = _end;
}

void	set_scene(t_scene *scene)
{
	double	ka;

	scene->canvas = canvas(WIN_WIDTH, WIN_HEIGHT);
	scene->cam = camera(new_point(0, 0, 5), new_point(0, 0, -1), 90);
	set_objects(scene->world);
	scene->rec.tmin = 0.00000001;
	scene->rec.tmax = MAXFLOAT;
	set_lights(scene->light);
	ka = 0.1;
	scene->ambient = vec_mul(new_color(1, 1, 1), ka);
}

int	main(int argc, char **argv)
{
	t_mlx		mlx;
	t_hit_array	objects_array[10];
	t_hit_array	lights_array[10];
	t_scene		scene;

	// arguments_check(argc, argv, &mlx);
	scene.world = objects_array;
	scene.light = lights_array;
	set_scene(&scene);
	
	initialize(argc, argv, &mlx);
	color_window(&mlx, &scene);
	set_hooks(&mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
