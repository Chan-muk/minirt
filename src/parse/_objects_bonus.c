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
	__check_parameter(array, hit_array, index, 3);
	free_double_array(array);
	(*index)++;
}

void	_parse_sphere(char *buffer, t_hit_array **hit_array, int *index)
{
	char	**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Error\nMemory problem in parse light.", EXIT_FAILURE);
	if (size_double_array(array) < 4)
	{
		free_double_array(array);
		exit_with_str("Error\nThe number of sphere parameters is wrong.", \
		EXIT_FAILURE);
	}
	(*hit_array)[*index].type = _sphere;
	(*hit_array)[*index].center = get_point(array[1]);
	(*hit_array)[*index].radius = (get_length(array[2]) * 0.5);
	__check_parameter(array, hit_array, index, 3);
	free_double_array(array);
	(*index)++;
}

void	_parse_cylinder(char *buffer, t_hit_array **hit_array, int *index)
{
	char		**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Error\nMemory problem in parse light.", EXIT_FAILURE);
	if (size_double_array(array) < 6)
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
	__check_parameter(array, hit_array, index, 5);
	free_double_array(array);
	(*index)++;
}

void	_parse_cone(char *buffer, t_hit_array **hit_array, int *index)
{
	char		**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Error\nMemory problem in parse light.", EXIT_FAILURE);
	if (size_double_array(array) < 6)
	{
		free_double_array(array);
		exit_with_str("Error\nThe number of cone parameters is wrong.", \
		EXIT_FAILURE);
	}
	(*hit_array)[*index].type = _cone;
	(*hit_array)[*index].center = get_point(array[1]);
	(*hit_array)[*index].norm = get_normal_vector(array[2]);
	(*hit_array)[*index].radius = (get_length(array[3]) * 0.5);
	(*hit_array)[*index].height = get_length(array[4]);
	__check_parameter(array, hit_array, index, 5);
	free_double_array(array);
	(*index)++;
}
