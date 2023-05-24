/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chajung <chajung@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 10:26:56 by chajung           #+#    #+#             */
/*   Updated: 2023/05/24 10:26:57 by chajung          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*find_node(t_list **head, int fd)
{
	t_list	*new_node;
	t_list	*temp;

	temp = (*head);
	while (temp)
	{
		if (temp->fd == fd)
			return (temp);
		if (!(temp->next))
			break ;
		temp = temp->next;
	}
	new_node = (t_list *)malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->backup = NULL;
	new_node->next = NULL;
	temp->next = new_node;
	return (new_node);
}

static t_list	*too_many_lines(t_list **head, int fd)
{
	t_list	*node;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!(*head))
	{
		*head = (t_list *)malloc(sizeof(t_list));
		if (!(*head))
			return (NULL);
		(*head)->fd = -2;
		(*head)->next = NULL;
		(*head)->backup = NULL;
	}
	node = find_node(head, fd);
	if (!node)
		return (NULL);
	if (!node->backup)
	{
		node->backup = (char *)malloc(sizeof(char));
		if (!node->backup)
			return (NULL);
		node->backup[0] = '\0';
	}
	return (node);
}

char	*get_next_line(int fd)
{
	static t_list	*head;
	t_list			*node;
	char			*line;

	node = too_many_lines(&head, fd);
	if (!node)
		return (NULL);
	line = read_line(node->backup, fd);
	if (!line)
	{
		clear_node(&head, node);
		return (NULL);
	}
	node->backup = clean_up(line);
	if (!(*line) && !(node->backup))
	{
		free(line);
		clear_node(&head, node);
		return (NULL);
	}
	return (line);
}
