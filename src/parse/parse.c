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
