/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:18:17 by chajung           #+#    #+#             */
/*   Updated: 2023/05/24 10:18:18 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#include "../libft/inc/get_next_line.h"
#include <fcntl.h>

typedef struct s_ambient_lightning_
{
	double			ratio;
	struct s_vector	color;
}	t_ambient_lightning_;

typedef struct s_camera_
{
	struct s_vector	view_point;
	struct s_vector	org_vector;
	double			fov;
}	t_camera_;

typedef struct s_light_
{
	struct s_vector	light_point;
	double			ratio;
	struct s_vector	color;
}	t_light_;

typedef struct s_sphere_
{
	struct s_vector	center;
	double			diameter;
	struct s_vector	color;
}	t_sphere_;

typedef struct s_plane_
{
	struct s_vector	center;
	struct s_vector	vector;
	struct s_vector	color;
}	t_plane_;

typedef struct s_cylinder_
{
	struct s_vector	center;
	struct s_vector	vector;
	double			diameter;
	double			height;
	struct s_vector	color;
}	t_cylinder_;

void	save_data(char *str)
{
	return ;
}

int	read_file(char *file)
{
	int fd;
	char *str;

	fd = open(file, O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		save_data(str);
		printf("%s", str);
		free(str);
	}
	close(fd);
	return (0);
}

int	is_rt_file(char *file)
{
	if (ft_strlen(file) >= 3 \
	&& ft_strncmp(".rt", &file[ft_strlen(file) - 3], 3) == 0)
		return (SUCCESS);
	return (FAILURE);
}

int	check_input(int argc, char **argv)
{
	if (argc != 2)
		return (FAILURE);
	if (is_rt_file(argv[1]) == FAILURE)
		return (FAILURE);
	read_file(argv[1]);
	return (SUCCESS);
}
