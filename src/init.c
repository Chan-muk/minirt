/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/01 09:05:19 by chajung           #+#    #+#             */
/*   Updated: 2023/05/01 09:05:21 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	init_mlx(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (!mlx->mlx_ptr)
		return (FAILURE);
	mlx->win_ptr = \
		mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "minirt");
	if (!mlx->mlx_ptr)
		return (FAILURE);
	mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, WIN_WIDTH, WIN_WIDTH);
	if (!mlx->img.img_ptr)
		return (FAILURE);
	mlx->img.data_addr = mlx_get_data_addr(mlx->img.img_ptr, \
		&mlx->img.bits_per_pixel, &mlx->img.size_line, &mlx->img.endian);
	if (!mlx->img.data_addr)
		return (FAILURE);
	return (SUCCESS);
}

void	initialize(int argc, char **argv, t_mlx *mlx)
{
	(void)argc;
	(void)argv;
	
	if (init_mlx(mlx) == FAILURE)
		exit_with_str("initialization failed in init_mlx", EXIT_FAILURE);
	// mlx->mlx_argc = argc;
	// mlx->mlx_argv = argv;
	// initialize_fractal_data(mlx);
}
