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

void	test_print_double_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
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
	{
		printf("sign: %d, dot: %d, c: %d\n", sign, dot, c);
		exit_with_str("The Number is not a double type.", EXIT_FAILURE);
	}
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

// int	ascii_to_int(const char *str)
// {
// 	int64_t	value;
// 	int		index;

// 	value = 0;
// 	index = 0;
// 	while (str[index])
// 	{
// 		if (ft_isdigit(str[index]) == FAILURE)
// 			return (FAILURE);
// 		value = value * 10 + (str[index] - '0');
// 		if (value > INT_MAX)
// 			return (FAILURE);
// 		index++;
// 	}
// 	if (value == 0)
// 		return (FAILURE);
// 	return ((int)value);
// }
