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

int	main(int argc, char **argv)
{
	t_mlx		mlx;
	t_hit_array	objects_array[10];
	t_hit_array	lights_array[10];
	t_scene		scene;

	parse("test.rt");
	return (0);

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
