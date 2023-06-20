/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:00:10 by chajung           #+#    #+#             */
/*   Updated: 2023/06/19 13:00:11 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_charset(char str, char *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (str == charset[i])
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	total_count(char *str, char *charset)
{
	int	count;

	count = 0;
	if (is_charset(*str, charset) == 0)
		count++;
	str++;
	while (*str)
	{
		if (!is_charset(*str, charset) && is_charset(*(str - 1), charset))
			count++;
		str++;
	}
	return (count);
}

int	str_count(char *str, char *charset)
{
	int	count;

	count = 0;
	if (is_charset(*str, charset))
		str++;
	while (*str && is_charset(*str, charset) == 0)
	{
		count++;
		str++;
	}
	return (count);
}

char	**make_arr(char **array, char *str, char *charset, int size)
{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (*str && is_charset(*str, charset))
			str++;
		array[i] = (char *)malloc(sizeof(char) * (str_count(str, charset) + 1));
		if (array[i] == NULL)
			return (0);
		while (*str && is_charset(*str, charset) == 0)
		{
			array[i][j] = *str;
			str++;
			j++;
		}
		array[i][j] = 0;
		i++;
	}
	return (array);
}

char	**_split(char *str, char *charset)
{
	int		size;
	char	**array;

	size = total_count(str, charset);
	array = (char **)malloc(sizeof(char *) * (size + 1));
	if (array == NULL)
		return (NULL);
	array = make_arr(array, str, charset, size);
	array[size] = NULL;
	return (array);
}
