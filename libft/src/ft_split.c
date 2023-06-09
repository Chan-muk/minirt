/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 13:59:14 by chajung           #+#    #+#             */
/*   Updated: 2022/11/13 20:54:00 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_double_arrayay(char **arrayay)
{
	int	i;

	i = -1;
	while (arrayay[++i])
	{
		free(arrayay[i]);
		arrayay[i] = NULL;
	}
	free(arrayay);
	arrayay = NULL;
	return (NULL);
}

static int	double_arrayay_size(char *str, char c)
{
	int	size;

	size = 0;
	if (*str && *str != c)
		size++;
	if (*str)
		str++;
	while (*str)
	{
		if (*str != c && *(str - 1) == c)
			size++;
		str++;
	}
	return (size);
}

static int	single_arrayay_size(char *str, char c)
{
	int	size;

	if (str == NULL)
		return (1);
	size = 0;
	if (*str == c)
		str++;
	while (*str && *str != c)
	{
		str++;
		size++;
	}
	return (size);
}

static int	make_arrayay(char **arrayay, char *str, char c, int size)
{
	int	i;
	int	j;

	i = -1;
	while (++i < size)
	{
		j = 0;
		while (*str && *str == c)
			str++;
		arrayay[i] = (char *)malloc(sizeof(char) \
			* (single_arrayay_size(str, c) + 1));
		if (arrayay[i] == NULL)
			return (FAILURE);
		while (*str && *str != c)
			arrayay[i][j++] = *str++;
		arrayay[i][j] = '\0';
	}
	arrayay[i] = NULL;
	return (SUCCESS);
}

char	**ft_split(char const *s, char c)
{
	int		size;
	char	**arrayay;

	size = double_arrayay_size((char *)s, c);
	arrayay = (char **)malloc(sizeof(char *) * (size + 1));
	if (arrayay == NULL)
		return (NULL);
	if (make_arrayay(arrayay, (char *)s, c, size) == FAILURE)
		return (free_double_arrayay(arrayay));
	return (arrayay);
}
