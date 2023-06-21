/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _objects.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:09:08 by chajung           #+#    #+#             */
/*   Updated: 2023/06/20 14:09:09 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	parse_light(char *buffer, t_hit_array **hit_array, int *index)
{
	char	**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Error\nMemory problem in parse light.", EXIT_FAILURE);
	if (size_double_array(array) != 3)
	{
		free_double_array(array);
		exit_with_str("Error\nThe number of light parameters is wrong.", \
		EXIT_FAILURE);
	}
	(*hit_array)[*index].type = _light;
	(*hit_array)[*index].center = get_point(array[1]);
	(*hit_array)[*index].bright_ratio = get_ratio(array[2]);
	(*hit_array)[*index].color = new_color(1, 1, 1);
	free_double_array(array);
	(*index)++;
}

void	parse_plane(char *buffer, t_hit_array **hit_array, int *index)
{
	char		**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Error\nMemory problem in parse light.", EXIT_FAILURE);
	if (size_double_array(array) != 4)
	{
		free_double_array(array);
		exit_with_str("Error\nThe number of plane parameters is wrong.", \
		EXIT_FAILURE);
	}
	(*hit_array)[*index].type = _plane;
	(*hit_array)[*index].center = get_point(array[1]);
	(*hit_array)[*index].norm = get_normal_vector(array[2]);
	(*hit_array)[*index].color = get_color(array[3]);
	(*hit_array)[*index].checker = false;
	free_double_array(array);
	(*index)++;
}

void	parse_sphere(char *buffer, t_hit_array **hit_array, int *index)
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
	(*hit_array)[*index].checker = false;
	free_double_array(array);
	(*index)++;
}

void	parse_cylinder(char *buffer, t_hit_array **hit_array, int *index)
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
	(*hit_array)[*index].checker = false;
	free_double_array(array);
	(*index)++;
}
