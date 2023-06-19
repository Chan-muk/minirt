/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/19 13:08:23 by chajung           #+#    #+#             */
/*   Updated: 2023/06/19 13:08:33 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

void	test_print_double_array(char **array);

/* parse */
int		parse(char *file_name);

/* split */
char	**_split(char *str, char *charset);

/* parse utils */
int		is_equal(char *str1, char *str2);
int		size_double_array(char **array);
char	**copy_double_array(char **origin_array);
void	free_double_array(char **array);

// int		ascii_to_int(const char *str);
double	ascii_to_double(char *str);

#endif
