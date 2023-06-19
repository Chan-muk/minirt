/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 11:26:59 by chajung           #+#    #+#             */
/*   Updated: 2023/06/19 11:27:00 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minirt.h"

// A	0.2 										255,255,255
// C	-50,0,2			0 0,0,0 	70
// L	-40,0,30 					0.7 			255,255,255
// pl	0,0,0 			0,1.0,0 					255,0,225
// sp	0,0,20 						20 				255,0,0
// cy	50.0,0.0,20.6 	0,0,1.0 	14.2 	21.42 	10,0,255

// void	check_parameter(char *buffer)
// {
// 	if (!ft_strncmp(buffer, "A", 1))
// 		printf("This is A\n");
// 	else if (!ft_strncmp(buffer, "C", 1))
// 		printf("This is C\n");
// 	else if (!ft_strncmp(buffer, "L", 1))
// 		printf("This is L\n");
// 	else if (!ft_strncmp(buffer, "sp", 2))
// 		printf("This is sp\n");
// 	else if (!ft_strncmp(buffer, "pl", 2))
// 		printf("This is pl\n");
// 	else if (!ft_strncmp(buffer, "cy", 2))
// 		printf("This is cy\n");
// 	else if (!ft_strncmp(buffer, "co", 2))
// 		printf("This is co\n");
// 	else if (!ft_strncmp(buffer, "\n", 1))
// 		printf("This is NL\n");
// 	else
// 		printf("Wrong Paramters: %s", buffer);
// }

/* SPLIT */
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

char	**make_arr(char **arr, char *str, char *charset, int length)
{
	int	i;
	int	j;

	i = 0;
	while (i < length)
	{
		j = 0;
		while (*str && is_charset(*str, charset))
			str++;
		arr[i] = (char *)malloc(sizeof(char) * (str_count(str, charset) + 1));
		if (arr[i] == NULL)
			return (0);
		while (*str && is_charset(*str, charset) == 0)
		{
			arr[i][j] = *str;
			str++;
			j++;
		}
		arr[i][j] = 0;
		i++;
	}
	return (arr);
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
/* SPLIT */

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

int	size_double_array(char **array)
{
	int	size;

	size = 0;
	while (array[size])
		size++;
	return (size);
}

int	is_equal(char *str1, char *str2)
{
	if (ft_strncmp(str1, str2, ft_strlen(str2)) == 0)
		return (TRUE);
	return (FALSE);
}

// int		parse_ambient_lightning(char *buffer)
// {
// 	char **array;

// 	array = ft_split()
// }

void	check_parameter(char *buffer)
{
	if (is_equal(buffer, "A"))
		printf("This is A\n");
	else if (is_equal(buffer, "C"))
		printf("This is C\n");
	else if (is_equal(buffer, "L"))
		printf("This is L\n");
	else if (is_equal(buffer, "pl"))
		printf("This is pl\n");
	else if (is_equal(buffer, "sp"))
		printf("This is sp\n");
	else if (is_equal(buffer, "cy"))
		printf("This is cy\n");
	else if (is_equal(buffer, "co"))
		printf("This is co\n");
	else if (is_equal(buffer, "\n"))
		printf("This is NL\n");
	else
		printf("Wrong Paramters: %s", buffer);
}

int	parse(char *file_name)
{
	int		fd;
	char	*buffer;

	/*
		1. When the file is empty
	*/
	
	fd = open(file_name, O_RDONLY);
	while (1)
	{
		buffer = get_next_line(fd);
		if (buffer == NULL)
			break ;
		// printf("%s", buffer);

		check_parameter(buffer);
		
		free(buffer);
	}
	close(fd);
	return (SUCCESS);
}