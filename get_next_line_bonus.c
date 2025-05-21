/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:15:23 by wheino            #+#    #+#             */
/*   Updated: 2025/05/21 13:42:56 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_operation(int fd, char *buf, char *stash)
{
	int		bytes_read;
	char	*temp_stash;

	if (ft_strchr(stash, '\n'))
		return (stash);
	while (1)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read <= 0)
			buf[0] = '\0';
		else
			buf[bytes_read] = '\0';
		temp_stash = ft_strjoin(stash, buf);
		free (stash);
		stash = temp_stash;
		if (ft_strchr(stash, '\n') != NULL || bytes_read <= 0)
			break ;
	}
	return (stash);
}

char	*extract_line(char **stash, char leftover[BUFFER_SIZE + 1])
{
	char	*line;
	char	*newline_i_ptr;
	int		newline_index;

	if (!stash || !*stash || **stash == '\0')
		return (NULL);
	newline_i_ptr = ft_strchr(*stash, '\n');
	if (newline_i_ptr)
	{
		newline_index = 0;
		while ((*stash)[newline_index] != '\n')
			newline_index++;
		line = ft_strldup(*stash, newline_index + 1);
		ft_strlcpy(leftover, newline_i_ptr + 1, BUFFER_SIZE + 1);
	}
	else
	{
		line = ft_strldup(*stash, ft_strlen(*stash));
		leftover[0] = '\0';
	}
	free(*stash);
	*stash = NULL;
	return (line);
}

void	ft_remove_node_fd(t_fd_node **head, t_fd_node *current)
{
	t_fd_node			*previous;

	if (*head == NULL || current == NULL)
		return ;
	if (*head == current)
	{
		*head = (*head)->next;
		free(current);
	}
	else
	{
		previous = *head;
		while (previous && previous->next != current)
			previous = previous->next;
		if (previous)
		{
			previous->next = current->next;
			free(current);
		}
	}
	return ;
}

t_fd_node	*find_or_create_node(t_fd_node **head, int fd)
{
	t_fd_node	**node;

	node = head;
	while (*node && (*node)->fd != fd)
		node = &(*node)->next;
	if (!*node)
	{
		*node = malloc(sizeof(t_fd_node));
		(*node)->fd = fd;
		(*node)->leftover[0] = '\0';
		(*node)->next = NULL;
	}
	return (*node);
}

char	*get_next_line(int fd)
{
	static t_fd_node	*head;
	t_fd_node			*current;
	char				*buf;
	char				*stash;
	char				*line;

	current = find_or_create_node(&head, fd);
	buf = malloc(BUFFER_SIZE + 1);
	if (!current->leftover[0])
		stash = ft_strldup("", 1);
	else
		stash = ft_strldup(current->leftover, ft_strlen(current->leftover));
	stash = read_operation(fd, buf, stash);
	free (buf);
	if (stash == NULL || *stash == '\0')
	{
		free (stash);
		ft_remove_node_fd(&head, current);
		return (NULL);
	}
	line = extract_line(&stash, current->leftover);
	return (line);
}
