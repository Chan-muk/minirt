/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 18:27:36 by chajung           #+#    #+#             */
/*   Updated: 2023/06/21 18:27:37 by chajung          ###   ########.fr       */
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

void	initialize_bonus(int argc, char **argv, t_mlx *mlx, t_scene *scene)
{
	t_hit_array	*array;

	if (argc != 2)
		exit_with_str("Error\nCheck arguments.", EXIT_FAILURE);
	if (is_rt_file(argv[1]) == FAILURE)
		exit_with_str("Error\nCheck RT file types.", EXIT_FAILURE);
	parse_bonus(argv[1], &array, scene);
	set_scene(scene);
	scene->world = array;
	if (init_mlx(mlx) == FAILURE)
		exit_with_str("Error\ninitialization failed in init_mlx", EXIT_FAILURE);
}
