/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:21:46 by chajung           #+#    #+#             */
/*   Updated: 2022/11/13 14:04:19 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	arrayay_size(int number)
{
	int	size;

	size = 0;
	if (number == 0)
		return (1);
	if (number < 0)
	{
		number /= -10;
		size += 2;
	}
	while (number > 0)
	{
		number /= 10;
		size++;
	}
	return (size);
}

static char	*int_to_ascii(char *arrayay, int number, size_t i)
{
	arrayay[i] = '\0';
	if (number == 0)
		arrayay[0] = '0';
	if (number < 0)
	{
		arrayay[0] = '-';
		arrayay[--i] = (number % 10) * (-1) + '0';
		number /= -10;
	}
	while (number > 0)
	{
		arrayay[--i] = number % 10 + '0';
		number /= 10;
	}
	return (arrayay);
}

char	*ft_itoa(int n)
{
	size_t	size;
	char	*arrayay;

	size = arrayay_size(n);
	arrayay = (char *)malloc(sizeof(char) * (size + 1));
	if (arrayay == NULL)
		return (NULL);
	arrayay = int_to_ascii(arrayay, n, size);
	return (arrayay);
}
