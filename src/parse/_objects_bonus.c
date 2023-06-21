/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _objects_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 17:07:35 by chajung           #+#    #+#             */
/*   Updated: 2023/06/21 17:07:36 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	_parse_light(char *buffer, t_hit_array **hit_array, int *index)
{
	char	**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Error\nMemory problem in parse light.", EXIT_FAILURE);
	if (size_double_array(array) != 4)
	{
		free_double_array(array);
		exit_with_str("Error\nThe number of light parameters is wrong.", \
		EXIT_FAILURE);
	}
	(*hit_array)[*index].type = _light;
	(*hit_array)[*index].center = get_point(array[1]);
	(*hit_array)[*index].bright_ratio = get_ratio(array[2]);
	(*hit_array)[*index].color = get_color(array[3]);
	free_double_array(array);
	(*index)++;
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

int	is_bmp_file(char *file)
{
	if (ft_strlen(file) >= 4 \
	&& ft_strncmp(".bmp", &file[ft_strlen(file) - 4], 4) == 0)
		return (SUCCESS);
	return (FAILURE);
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

void	_parse_plane(char *buffer, t_hit_array **hit_array, int *index)
{
	char		**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Error\nMemory problem in parse light.", EXIT_FAILURE);
	if (size_double_array(array) < 4)
	{
		free_double_array(array);
		exit_with_str("Error\nThe number of plane parameters is wrong.", \
		EXIT_FAILURE);
	}
	(*hit_array)[*index].type = _plane;
	(*hit_array)[*index].center = get_point(array[1]);
	(*hit_array)[*index].norm = get_normal_vector(array[2]);
	// (*hit_array)[*index].color = get_color(array[3]);
	(*hit_array)[*index].checker = false;
	if (is_equal(array[3], "CHECKER"))
		__checker(array, hit_array, index, 3);
	else if (is_equal(array[3], "COLOR"))
		__color(array, hit_array, index, 3);
	else if (is_equal(array[3], "TEXTURE"))
		__texture(array, hit_array, index, 3);
	

	
	free_double_array(array);
	(*index)++;
}

void	_parse_sphere(char *buffer, t_hit_array **hit_array, int *index)
{
	char	**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Error\nMemory problem in parse light.", EXIT_FAILURE);
	if (size_double_array(array) != 4)
	{
		free_double_array(array);
		exit_with_str("Error\nThe number of sphere parameters is wrong.", \
		EXIT_FAILURE);
	}
	(*hit_array)[*index].type = _sphere;
	(*hit_array)[*index].center = get_point(array[1]);
	(*hit_array)[*index].radius = (get_length(array[2]) * 0.5);
	(*hit_array)[*index].color = get_color(array[3]);
	free_double_array(array);
	(*index)++;
}

void	_parse_cylinder(char *buffer, t_hit_array **hit_array, int *index)
{
	char		**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Error\nMemory problem in parse light.", EXIT_FAILURE);
	if (size_double_array(array) != 6)
	{
		free_double_array(array);
		exit_with_str("Error\nThe number of cylinder parameters is wrong.", \
		EXIT_FAILURE);
	}
	(*hit_array)[*index].type = _cylinder;
	(*hit_array)[*index].center = get_point(array[1]);
	(*hit_array)[*index].norm = get_normal_vector(array[2]);
	(*hit_array)[*index].radius = (get_length(array[3]) * 0.5);
	(*hit_array)[*index].height = get_length(array[4]);
	(*hit_array)[*index].color = get_color(array[5]);
	free_double_array(array);
	(*index)++;
}

void	_parse_cone(char *buffer, t_hit_array **hit_array, int *index)
{
	char		**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Error\nMemory problem in parse light.", EXIT_FAILURE);
	if (size_double_array(array) != 6)
	{
		free_double_array(array);
		exit_with_str("Error\nThe number of cylinder parameters is wrong.", \
		EXIT_FAILURE);
	}
	(*hit_array)[*index].type = _cone;
	(*hit_array)[*index].center = get_point(array[1]);
	(*hit_array)[*index].norm = get_normal_vector(array[2]);
	(*hit_array)[*index].radius = (get_length(array[3]) * 0.5);
	(*hit_array)[*index].height = get_length(array[4]);
	(*hit_array)[*index].color = get_color(array[5]);
	free_double_array(array);
	(*index)++;
}
