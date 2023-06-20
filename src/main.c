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

void	__test_print_hit_array(t_hit_array *array)
{
	int	i;

	i = 0;
	// printf("%d\n", array[i].type);
	while (array[i].type != 0)
	{
		printf("type: %d\n", array[i].type);
		printf("center x: %f, y: %f, z: %f\n", array[i].center.x, array[i].center.y, array[i].center.z);
		printf("norm x: %f, y: %f, z: %f\n", array[i].norm.x, array[i].norm.y, array[i].norm.z);
		printf("color x: %f, y: %f, z: %f\n", array[i].color.x, array[i].color.y, array[i].color.z);
		printf("radius: %f\n", array[i].radius);
		printf("height: %f\n", array[i].height);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_mlx		mlx;
	t_hit_array	*array;
	t_scene		scene;

	parse("test.rt", &array, &scene);
	// __test_print_hit_array(array);

	// arguments_check(argc, argv, &mlx);

	(&scene)->world = array;

	set_scene(&scene);

	initialize(argc, argv, &mlx);

	color_window(&mlx, &scene);
	set_hooks(&mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
