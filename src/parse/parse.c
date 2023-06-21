/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:26:59 by chajung           #+#    #+#             */
/*   Updated: 2023/06/19 11:27:00 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_rt_parameter(int fd, int *count, int *count_a, int *count_c)
{
	char	*buffer;

	while (TRUE)
	{
		buffer = get_next_line(fd);
		if (buffer == NULL)
			break ;
		if (is_equal(buffer, "A"))
			(*count_a)++;
		else if (is_equal(buffer, "C"))
			(*count_c)++;
		else if (is_equal(buffer, "L") || is_equal(buffer, "pl") \
		|| is_equal(buffer, "sp") || is_equal(buffer, "cy") \
		|| is_equal(buffer, "co"))
			(*count)++;
		else if (is_equal(buffer, "\n"))
			;
		else
			exit_with_str("Error\nThere is wrong Paramter.", EXIT_FAILURE);
		free(buffer);
	}
	if ((*count_a) == 0 || (*count_c) == 0)
		exit_with_str("Error\nAmbient light and Camera must exist.", \
		EXIT_FAILURE);
}

int	get_hit_array_size(char *file_name)
{
	int	fd;
	int	count;
	int	count_a;
	int	count_c;

	fd = open(file_name, O_RDONLY);
	count = 0;
	count_a = 0;
	count_c = 0;
	check_rt_parameter(fd, &count, &count_a, &count_c);
	if ((count_a + count_c + count) == 0)
		exit_with_str("Error\nCheck the RT file.", EXIT_FAILURE);
	close(fd);
	return (count);
}

void	check_parameter(char *buffer, t_hit_array **array, t_scene *scene, \
int *index)
{
	if (is_equal(buffer, "A"))
		parse_ambient_lightning(buffer, scene);
	else if (is_equal(buffer, "C"))
		parse_camera(buffer, scene);
	else if (is_equal(buffer, "L"))
		parse_light(buffer, array, index);
	else if (is_equal(buffer, "pl"))
		parse_plane(buffer, array, index);
	else if (is_equal(buffer, "sp"))
		parse_sphere(buffer, array, index);
	else if (is_equal(buffer, "cy"))
		parse_cylinder(buffer, array, index);
	else if (is_equal(buffer, "co"))
		parse_cone(buffer, array, index);
	else if (is_equal(buffer, "\n"))
		;
	else
		printf("Wrong Paramters: %s", buffer);
}

void	parse(char *file_name, t_hit_array **array, t_scene *scene)
{
	int		fd;
	int		size;
	int		index;
	char	*buffer;

	size = get_hit_array_size(file_name);
	fd = open(file_name, O_RDONLY);
	*array = ft_calloc(sizeof(t_hit_array), (size + 1));
	if (*array == NULL || scene == NULL)
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
