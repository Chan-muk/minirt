/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils0.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:07:39 by chajung           #+#    #+#             */
/*   Updated: 2023/06/19 13:07:42 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	get_ratio(char *str)
{
	double	ratio;

	ratio = ascii_to_double(str);
	if (ratio < 0.0 || ratio > 1.0)
		exit_with_str("Ratio is out of range.", EXIT_FAILURE);
	return (ratio);
}

double	get_length(char *str)
{
	double	length;

	length = ascii_to_double(str);
	if (length <= 0.0)
		exit_with_str("Length must be greater than zero.", EXIT_FAILURE);
	return (length);
}

t_color	get_color(char *str)
{
	char	**array;
	t_color	color;

	array = _split(str, ",");
	if (array == NULL)
		exit_with_str("Memory problem in get color.", EXIT_FAILURE);
	color.x = ascii_to_double(array[0]);
	color.y = ascii_to_double(array[1]);
	color.z = ascii_to_double(array[2]);
	free_double_array(array);
	if (color.x < 0.0 || color.x > 255.0 || color.y < 0.0 \
	|| color.y > 255.0 || color.z < 0.0 || color.z > 255.0)
		exit_with_str("Color is out of range.", EXIT_FAILURE);
	return (color);
}

t_point	get_point(char *str)
{
	char	**array;
	t_point	point;

	array = _split(str, ",");
	if (array == NULL)
		exit_with_str("Memory problem in get point.", EXIT_FAILURE);
	point.x = ascii_to_double(array[0]);
	point.y = ascii_to_double(array[1]);
	point.z = ascii_to_double(array[2]);
	free_double_array(array);
	return (point);
}

t_vector	get_normal_vector(char *str)
{
	char		**array;
	t_vector	vector;

	array = _split(str, ",");
	if (array == NULL)
		exit_with_str("Memory problem in get vector.", EXIT_FAILURE);
	vector.x = ascii_to_double(array[0]);
	vector.y = ascii_to_double(array[1]);
	vector.z = ascii_to_double(array[2]);
	free_double_array(array);
	if (vector.x < -1.0 || vector.x > 1.0 || vector.y < -1.0 \
	|| vector.y > 1.0 || vector.z < -1.0 || vector.z > 1.0)
		exit_with_str("Normal Vector is out of range.", EXIT_FAILURE);
	return (unit_vec(vector));
}
