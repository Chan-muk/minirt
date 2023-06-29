/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _scene.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:11:42 by chajung           #+#    #+#             */
/*   Updated: 2023/06/20 14:11:43 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	get_fov(char *str)
{
	double	fov;

	fov = ascii_to_double(str);
	if (fov < 0.0 || fov > 180.0)
		exit_with_str("FOV is out of range.", EXIT_FAILURE);
	return (fov);
}

void	parse_ambient_lightning(char *buffer, t_scene *scene)
{
	char	**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Memory problem in parse ambient light.", \
		EXIT_FAILURE);
	if (size_double_array(array) != 3)
	{
		free_double_array(array);
		exit_with_str("The number of ambient light parameters is wrong.", \
		EXIT_FAILURE);
	}
	scene->ambient_ratio = get_ratio(array[1]);
	scene->color = get_color(array[2]);
	scene->ambient = vec_mul(scene->color, scene->ambient_ratio);
	free_double_array(array);
}

void	parse_camera(char *buffer, t_scene *scene)
{
	char		**array;

	array = _split(buffer, DELIMITER);
	if (array == NULL)
		exit_with_str("Memory problem in parse camera.", EXIT_FAILURE);
	if (size_double_array(array) != 4)
	{
		free_double_array(array);
		exit_with_str("The number of camera parameters is wrong.", \
		EXIT_FAILURE);
	}
	scene->cam_org = get_point(array[1]);
	scene->cam_dir = get_normal_vector(array[2]);
	scene->cam_fov = get_fov(array[3]);
	free_double_array(array);
}
