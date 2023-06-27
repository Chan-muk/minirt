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
	// t_mlx		mlx;
	// t_scene		scene;
	t_data	data;

	// initialize(argc, argv, &mlx, &scene);
	initialize(argc, argv, &data);
	// color_window(&mlx, &scene);
	// set_hooks(&mlx);
	color_window(&data.mlx, &data.scene);
	set_hooks(&data.mlx);
	mlx_loop(data.mlx.mlx_ptr);
	return (0);
}
