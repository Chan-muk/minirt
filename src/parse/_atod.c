/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _atod.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:19:58 by chajung           #+#    #+#             */
/*   Updated: 2023/06/20 14:19:59 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	white_space_sign_check(char *str, int *index)
{
	int	sign;

	sign = 1;
	while ((9 <= str[*index] && str[*index] <= 13) || str[*index] == 32)
		*index += 1;
	if (str[*index] == '+' || str[*index] == '-')
	{
		if (str[*index] == '-')
			sign = sign * (-1);
		*index += 1;
	}
	return (sign);
}

static void	is_double(char *str)
{
	int	sign;
	int	c;
	int	dot;

	sign = 0;
	c = 0;
	dot = 0;
	while (str && *str)
	{
		if (*str == '+' || *str == '-')
			sign++;
		else if (*str == '.')
			dot++;
		else if (!ft_isdigit(*str) && ft_isascii(*str))
			c++;
		str++;
	}
	if (!str || sign > 1 || dot > 1 || c > 0)
		exit_with_str("Error\nThe Number is incorrect.", EXIT_FAILURE);
}

void	init_variable(int *index, int *count, int *d_count, double *number)
{
	*index = 0;
	*count = 0;
	*d_count = 0;
	*number = 0.0;
}

double	ascii_to_double(char *str)
{
	int		index;
	int		sign;
	int		count[2];
	double	number;

	is_double(str);
	init_variable(&index, &count[0], &count[1], &number);
	sign = white_space_sign_check(str, &index);
	while (str[index] && ft_isdigit(str[index]))
	{
		number = 10.0 * number + (str[index] - '0');
		index++;
		(count[0])++;
	}
	if (str[index] == '.')
		index++;
	while (str[index] && ft_isdigit(str[index]))
	{
		number = 10.0 * number + (str[index] - '0');
		index++;
		(count[1])++;
	}
	if (count[0] > 10 || count[1] > 10)
		exit_with_str("Check the number", EXIT_FAILURE);
	return (sign * number * pow(0.1, count[1]));
}
