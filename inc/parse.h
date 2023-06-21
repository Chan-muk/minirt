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

typedef struct s_counts	t_counts;

struct s_counts
{
	int	amb;
	int	cam;
	int	light;
	int	pl;
	int	sp;
	int	cy;
	int	co;
};

/* parse */
void		parse(char *file_name, t_hit_array **array, t_scene *scene);

/* parse_bonus */
void		parse_bonus(char *file_name, t_hit_array **array, t_scene *scene);

/* _scene */
void		parse_ambient_lightning(char *buffer, t_scene *scene);
void		parse_camera(char *buffer, t_scene *scene);

/* _objects */
void		parse_light(char *buffer, t_hit_array **hit_array, int *index);
void		parse_plane(char *buffer, t_hit_array **hit_array, int *index);
void		parse_sphere(char *buffer, t_hit_array **hit_array, int *index);
void		parse_cylinder(char *buffer, t_hit_array **hit_array, int *index);

/* _objects_bonus */
void		_parse_light(char *buffer, t_hit_array **hit_array, int *index);
void		_parse_plane(char *buffer, t_hit_array **hit_array, int *index);
void		_parse_sphere(char *buffer, t_hit_array **hit_array, int *index);
void		_parse_cylinder(char *buffer, t_hit_array **hit_array, int *index);
void		_parse_cone(char *buffer, t_hit_array **hit_array, int *index);

/* _atod */
double		ascii_to_double(char *str);

/* _split */
char		**_split(char *str, char *charset);

/* _utils0 */
double		get_ratio(char *str);
double		get_length(char *str);
t_color		get_color(char *str);
t_point		get_point(char *str);
t_vector	get_normal_vector(char *str);

/* _utils0 */
void		init_counts_data(t_counts *counts);
int			get_counts_data(t_counts counts);
int			is_equal(char *str1, char *str2);
int			size_double_array(char **array);
void		free_double_array(char **array);

/* _utils_bonus */
void	__check_parameter(char **array, t_hit_array **hit_array, int *index, int column);
void	__checker(char **array, t_hit_array **hit_array, int *index, int column);
void	__color(char **array, t_hit_array **hit_array, int *index, int column);
void	__texture(char **array, t_hit_array **hit_array, int *index, int column);

#endif
