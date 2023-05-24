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

int read_file(char *file)
{
	int fd;
	char *str;

	fd = open(file, O_RDONLY);
	while (1)
	{
		str = get_next_line(fd);
		if (str == NULL)
			break ;
		printf("%s", str);
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

int check_input(int argc, char **argv)
{
	if (argc != 2)
		return (FAILURE);
	if (is_rt_file(argv[1]) == FAILURE)
		return (FAILURE);
	read_file(argv[1]);
	return (SUCCESS);
}