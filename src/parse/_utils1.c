/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _utils1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:18:51 by chajung           #+#    #+#             */
/*   Updated: 2023/06/20 14:18:52 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	init_counts_data(t_counts *counts)
{
	counts->amb = 0;
	counts->cam = 0;
	counts->light = 0;
	counts->pl = 0;
	counts->sp = 0;
	counts->cy = 0;
	counts->co = 0;
}

int	get_counts_data(t_counts counts)
{
	int	result;

	result = counts.amb + counts.cam + counts.light + \
	counts.pl + counts.sp + counts.cy + counts.co;
	return (result);
}

int	is_equal(char *str1, char *str2)
{
	if (ft_strncmp(str1, str2, ft_strlen(str2)) == 0)
		return (TRUE);
	return (FALSE);
}

int	size_double_array(char **array)
{
	int	size;

	size = 0;
	while (array[size])
		size++;
	return (size);
}

void	free_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
	array = NULL;
}
