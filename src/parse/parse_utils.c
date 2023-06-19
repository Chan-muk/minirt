/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:07:39 by chajung           #+#    #+#             */
/*   Updated: 2023/06/19 13:07:42 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

char	**copy_double_array(char **origin_array)
{
	int		i;
	int		size;
	char	**copied_array;

	size = 0;
	while (origin_array[size])
		size++;
	copied_array = (char **)malloc(sizeof(char *) * (size + 1));
	if (!copied_array)
		return (NULL);
	i = 0;
	while (origin_array[i])
	{
		copied_array[i] = ft_strdup(origin_array[i]);
		if (!copied_array)
			return (NULL);
		i++;
	}
	copied_array[i] = NULL;
	return (copied_array);
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
	array = NULL;
}
