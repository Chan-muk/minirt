/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:27:51 by chajung           #+#    #+#             */
/*   Updated: 2023/06/21 18:27:52 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	t_mlx		mlx;
	t_scene		scene;

	initialize_bonus(argc, argv, &mlx, &scene);
	color_window(&mlx, &scene);
	set_hooks(&mlx);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}
