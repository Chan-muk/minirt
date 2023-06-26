/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/21 16:47:28 by chajung           #+#    #+#             */
/*   Updated: 2023/06/21 16:47:29 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	check_rt_parameter(int fd, t_counts *counts, char *buffer)
{
	while (TRUE)
	{
		buffer = get_next_line(fd);
		if (buffer == NULL)
			break ;
		if (is_equal(buffer, "A"))
			(counts->amb)++;
		else if (is_equal(buffer, "C"))
			(counts->cam)++;
		else if (is_equal(buffer, "L"))
			(counts->light)++;
		else if (is_equal(buffer, "pl"))
			(counts->pl)++;
		else if (is_equal(buffer, "sp"))
			(counts->sp)++;
		else if (is_equal(buffer, "cy"))
			(counts->cy)++;
		else if (is_equal(buffer, "co"))
			(counts->cy)++;
		else if (is_equal(buffer, "\n"))
			;
		else
			exit_with_str("Error\nThere is wrong paramter.", EXIT_FAILURE);
		free(buffer);
	}
}

static int	get_hit_array_size(char *file_name)
{
	int			fd;
	t_counts	counts;
	char		*buffer;
	int			all_count;

	fd = open(file_name, O_RDONLY);
	if (fd == FAILURE)
		exit_with_str("Error\nFile open fail.", EXIT_FAILURE);
	init_counts_data(&counts);
	check_rt_parameter(fd, &counts, buffer);
	all_count = get_counts_data(counts);
	if (all_count == 0)
		exit_with_str("Error\nRT File is empty.", EXIT_FAILURE);
	if (counts.amb != 1 || counts.cam != 1 || counts.light < 1)
		exit_with_str("Error\nThere are no essential components.", EXIT_FAILURE);
	close(fd);
	return (all_count);
}

static void	check_parameter(char *buffer, t_hit_array **array, t_scene *scene, \
int *index)
{
	if (is_equal(buffer, "A"))
		parse_ambient_lightning(buffer, scene);
	else if (is_equal(buffer, "C"))
		parse_camera(buffer, scene);
	else if (is_equal(buffer, "L"))
		_parse_light(buffer, array, index);
	else if (is_equal(buffer, "pl"))
		_parse_plane(buffer, array, index);
	else if (is_equal(buffer, "sp"))
		_parse_sphere(buffer, array, index);
	else if (is_equal(buffer, "cy"))
		_parse_cylinder(buffer, array, index);
	else if (is_equal(buffer, "co"))
		_parse_cone(buffer, array, index);
	else if (is_equal(buffer, "\n"))
		;
	else
		exit_with_str("Error\nWrong parameter.", EXIT_FAILURE);
}

void	parse_bonus(char *file_name, t_hit_array **array, t_scene *scene)
{
	int		fd;
	int		size;
	int		index;
	char	*buffer;

	size = get_hit_array_size(file_name);
	fd = open(file_name, O_RDONLY);
	if (fd == FAILURE)
		exit_with_str("Error\nFile open fail.", EXIT_FAILURE);
	*array = ft_calloc(sizeof(t_hit_array), (size + 1));
	if (*array == NULL)
		exit_with_str("Error\nMemory problem in parse.", EXIT_FAILURE);
	index = 0;
	while (TRUE)
	{
		buffer = get_next_line(fd);
		if (buffer == NULL)
			break ;
		check_parameter(buffer, array, scene, &index);
		free(buffer);
	}
	close(fd);
}
