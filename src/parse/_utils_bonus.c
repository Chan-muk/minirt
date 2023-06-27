/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:59:52 by chajung           #+#    #+#             */
/*   Updated: 2023/06/21 17:59:53 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	is_xpm_file(char *file)
{
	if (ft_strlen(file) >= 4 \
	&& !ft_strncmp(".xpm", &file[ft_strlen(file) - 4], 4))
		return (SUCCESS);
	return (FAILURE);
}

void	__checker(char **array, t_data *data, int *index, int column)
{
	if (size_double_array(array) != (column + 1))
	{
		free_double_array(array);
		exit_with_str("Error\nChecker board parameters are not correct.", \
		EXIT_FAILURE);
	}
	data->scene.world[*index].flag = _checker;
}

void	__color(char **array, t_data *data, int *index, int column)
{
	if (size_double_array(array) != (column + 2))
	{
		free_double_array(array);
		exit_with_str("Error\nColor parameters are not correct.", \
		EXIT_FAILURE);
	}
	data->scene.world[*index].color = get_color(array[column + 1]);
	data->scene.world[*index].flag = _color;
}

void	__texture(char **array, t_data *data, int *index, int column)
{
	void	*ptr;
	void	*ptr2;

	if (size_double_array(array) != (column + 3))
	{
		free_double_array(array);
		exit_with_str("Error\nTexture parameters are not correct.", \
		EXIT_FAILURE);
	}
	if (is_xpm_file(array[column + 1]) == FAILURE \
	|| is_xpm_file(array[column + 2]) == FAILURE)
		exit_with_str("Error\nCheck XPM file types.", EXIT_FAILURE);
	// data->scene.world[*index].texture.addr = mlx_xpm_file_to_image(&(data->mlx.mlx_ptr), array[column + 1], &width, &height);

	ptr = mlx_xpm_file_to_image(&(data->mlx.mlx_ptr), array[column + 1], &(data->scene.world->texture.w), &(data->scene.world->texture.h));
	data->scene.world[*index].texture.addr = ptr;
	// data->scene.world[*index].texture.addr = mlx_get_data_addr(ptr, &(data->mlx.img.bits_per_pixel), &(data->mlx.img.size_line), &(data->mlx.img.endian));

	ptr2 = mlx_xpm_file_to_image(&(data->mlx.mlx_ptr), array[column + 2], &(data->scene.world->bump_map.w), &(data->scene.world->bump_map.h));
	data->scene.world[*index].bump_map.addr = ptr2;
	// data->scene.world[*index].bump_map.addr = mlx_get_data_addr(ptr2, &(data->mlx.img.bits_per_pixel), &(data->mlx.img.size_line), &(data->mlx.img.endian));

	// printf("p1: %p, p2: %p\n", ptr, ptr2);
	// printf("p1: %p, p2: %p\n", data->scene.world[*index].texture.addr, data->scene.world[*index].bump_map.addr);
	// exit(1);

	// data->scene.world[*index].bump_map.addr = mlx_xpm_file_to_image(&(data->mlx.mlx_ptr), array[column + 2], &width, &height);
	// if (data->scene.world[*index].texture.addr == NULL || data->scene.world[*index].texture.addr == NULL)
	// 	exit_with_str("Error\nMLX Error.", EXIT_FAILURE);
	// get_bmp_addr(array[column + 1], &(data->scene.world[*index].texture));
	// get_bmp_addr(array[column + 2], &(data->scene.world[*index].bump_map));
	data->scene.world[*index].flag = _texture;
}

void	__check_parameter(char **array, t_data *data, int *index, int column)
{
	if (is_equal(array[column], "CHECKER"))
		__checker(array, data, index, column);
	else if (is_equal(array[column], "COLOR"))
		__color(array, data, index, column);
	else if (is_equal(array[column], "TEXTURE"))
		__texture(array, data, index, column);
	else
		exit_with_str("Error\nLast parameter is incorrect.", EXIT_FAILURE);
}
