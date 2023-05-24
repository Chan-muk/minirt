/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.k>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:38:37 by chajung           #+#    #+#             */
/*   Updated: 2023/05/24 10:38:38 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*clean_up(char *line)
{
	int		i;
	char	*temp;

	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
		return (NULL);
	temp = ft_substr(line, i + 1, ft_strlen(line));
	if (!temp)
		return (NULL);
	line[i + 1] = '\0';
	return (temp);
}

char	*read_line(char *backup, int fd)
{
	int		read_byte;
	char	*temp;
	char	*buffer;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	read_byte = 0;
	while (!ft_strchr(backup, '\n'))
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte <= 0)
			break ;
		buffer[read_byte] = '\0';
		temp = backup;
		backup = ft_strjoin(temp, buffer);
		if (!backup)
			break ;
		free(temp);
	}
	free(buffer);
	if (read_byte < 0)
		return (NULL);
	return (backup);
}

void	clear_node(t_list **head, t_list *node)
{
	t_list	*temp;
	t_list	*prev_node;
	int		list_size;

	list_size = 0;
	temp = (*head);
	while (temp->next)
	{
		if (temp->next == node)
			prev_node = temp;
		temp = temp->next;
		list_size++;
	}
	prev_node->next = node->next;
	free(node->backup);
	free(node);
	if (list_size == 1)
	{
		free(*head);
		*head = NULL;
	}
}
