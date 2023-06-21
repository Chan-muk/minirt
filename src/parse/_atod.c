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

double	ascii_to_double(char *str)
{
	int		index;
	int		sign;
	int		decimal_count;
	double	number;

	index = 0;
	decimal_count = 0;
	number = 0.0;
	is_double(str);
	sign = white_space_sign_check(str, &index);
	while (str[index] && ft_isdigit(str[index]))
	{
		number = 10.0 * number + (str[index] - '0');
		index++;
	}
	if (str[index] == '.')
		index++;
	while (str[index] && ft_isdigit(str[index]))
	{
		number = 10.0 * number + (str[index] - '0');
		index++;
		decimal_count++;
	}
	return (sign * number * pow(0.1, decimal_count));
}
