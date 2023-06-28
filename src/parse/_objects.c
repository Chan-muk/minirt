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

void	parse_light(char *buffer, t_data *data, int *index)
{
	char	**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Memory problem in parse light.", EXIT_FAILURE);
	if (size_double_array(array) != 3)
	{
		free_double_array(array);
		exit_with_str("The number of light parameters is wrong.", \
		EXIT_FAILURE);
	}
	data->scene.world[*index].type = _light;
	data->scene.world[*index].center = get_point(array[1]);
	data->scene.world[*index].bright_ratio = get_ratio(array[2]);
	data->scene.world[*index].color = new_color(1, 1, 1);
	free_double_array(array);
	(*index)++;
}

void	parse_plane(char *buffer, t_data *data, int *index)
{
	char		**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Memory problem in parse plane.", EXIT_FAILURE);
	if (size_double_array(array) != 4)
	{
		free_double_array(array);
		exit_with_str("The number of plane parameters is wrong.", \
		EXIT_FAILURE);
	}
	data->scene.world[*index].type = _plane;
	data->scene.world[*index].center = get_point(array[1]);
	data->scene.world[*index].norm = get_normal_vector(array[2]);
	data->scene.world[*index].color = get_color(array[3]);
	data->scene.world[*index].flag = _color;
	free_double_array(array);
	(*index)++;
}

void	parse_sphere(char *buffer, t_data *data, int *index)
{
	char	**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Memory problem in parse sphere.", EXIT_FAILURE);
	if (size_double_array(array) != 4)
	{
		free_double_array(array);
		exit_with_str("The number of sphere parameters is wrong.", \
		EXIT_FAILURE);
	}
	data->scene.world[*index].type = _sphere;
	data->scene.world[*index].center = get_point(array[1]);
	data->scene.world[*index].radius = (get_length(array[2]) * 0.5);
	data->scene.world[*index].color = get_color(array[3]);
	data->scene.world[*index].flag = _color;
	free_double_array(array);
	(*index)++;
}

void	parse_cylinder(char *buffer, t_data *data, int *index)
{
	char		**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Memory problem in parse cylinder.", EXIT_FAILURE);
	if (size_double_array(array) != 6)
	{
		free_double_array(array);
		exit_with_str("The number of cylinder parameters is wrong.", \
		EXIT_FAILURE);
	}
	data->scene.world[*index].type = _cylinder;
	data->scene.world[*index].center = get_point(array[1]);
	data->scene.world[*index].norm = get_normal_vector(array[2]);
	data->scene.world[*index].radius = (get_length(array[3]) * 0.5);
	data->scene.world[*index].height = get_length(array[4]);
	data->scene.world[*index].color = get_color(array[5]);
	data->scene.world[*index].flag = _color;
	free_double_array(array);
	(*index)++;
}
