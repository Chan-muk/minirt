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

static int	init_mlx(t_mlx *mlx)
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

static int	is_rt_file(char *file)
{
	if (ft_strlen(file) >= 3 \
	&& ft_strncmp(".rt", &file[ft_strlen(file) - 3], 3) == 0)
		return (SUCCESS);
	return (FAILURE);
}

void	initialize(int argc, char **argv, t_data *data)
{
	if (argc != 2)
		exit_with_str("Check the number of arguments.", EXIT_FAILURE);
	if (is_rt_file(argv[1]) == FAILURE)
		exit_with_str("Check RT file types.", EXIT_FAILURE);
	parse(argv[1], data);
	data->scene.cam = \
	set_camera(data->scene.cam_org, data->scene.cam_dir, data->scene.cam_fov);
	if (init_mlx(&(data->mlx)) == FAILURE)
		exit_with_str("Initialization failed in init mlx", EXIT_FAILURE);
}
