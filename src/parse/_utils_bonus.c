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

static int	is_bmp_file(char *file)
{
	if (ft_strlen(file) >= 4 \
	&& ft_strncmp(".bmp", &file[ft_strlen(file) - 4], 4) == 0)
		return (SUCCESS);
	return (FAILURE);
}

void	__checker(char **array, t_hit_array **hit_array, int *index, int column)
{
	if (size_double_array(array) != (column + 1))
	{
		free_double_array(array);
		exit_with_str("Error\nChecker board parameters are not correct.", \
		EXIT_FAILURE);
	}
	(*hit_array)[*index].flag = _checker;
}

void	__color(char **array, t_hit_array **hit_array, int *index, int column)
{
	if (size_double_array(array) != (column + 2))
	{
		free_double_array(array);
		exit_with_str("Error\Color parameters are not correct.", \
		EXIT_FAILURE);
	}
	(*hit_array)[*index].color = get_color(array[column + 1]);
	(*hit_array)[*index].flag = _color;
}

void	__texture(char **array, t_hit_array **hit_array, int *index, int column)
{
	if (size_double_array(array) != (column + 3))
	{
		free_double_array(array);
		exit_with_str("Error\nTexture parameters are not correct.", \
		EXIT_FAILURE);
	}
	if (is_bmp_file(array[column + 1]) == FAILURE \
	|| is_bmp_file(array[column + 1]) == FAILURE)
		exit_with_str("Error\nCheck BMP file types.", EXIT_FAILURE);
	get_bmp_addr(array[column + 1], &((*hit_array)[*index].texture));
	get_bmp_addr(array[column + 2], &((*hit_array)[*index].bump_map));
	(*hit_array)[*index].flag = _texture;
}

void	__check_parameter(char **array, t_hit_array **hit_array, int *index, int column)
{
	if (is_equal(array[column], "CHECKER"))
		__checker(array, hit_array, index, column);
	else if (is_equal(array[column], "COLOR"))
		__color(array, hit_array, index, column);
	else if (is_equal(array[column], "TEXTURE"))
		__texture(array, hit_array, index, column);
	else
		exit_with_str("Error\nLast parameter is incorrect.", EXIT_FAILURE);
}