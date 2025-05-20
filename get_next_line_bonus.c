/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:15:23 by wheino            #+#    #+#             */
/*   Updated: 2025/05/19 22:52:04 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*read_operation(int fd, char *buf, char *stash)
{
	int		bytes_read;
	char	*temp_stash;

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

char	*extract_line(char **stash)
{
	char	*trimmed_stash;
	char	*line;
	char	*newline_i_ptr;
	int		newline_index;

	newline_i_ptr = ft_strchr(*stash, '\n');
	if (newline_i_ptr)
	{
		newline_index = 0;
		while ((*stash)[newline_index] != '\n')
			newline_index++;
		line = ft_strldup(*stash, newline_index + 1);
		trimmed_stash = ft_strdup(newline_i_ptr + 1);
		free(*stash);
		*stash = trimmed_stash;
	}
	else
	{
		line = ft_strdup(*stash);
		free(*stash);
		*stash = NULL;
	}
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
		free(current->stash);
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
			free(current->stash);
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
		(*node)->stash = ft_strdup("");
		(*node)->next = NULL;
	}
	return (*node);
}

char	*get_next_line(int fd)
{
	static t_fd_node	*head;
	t_fd_node			*current;
	char				*buf;
	char				*line;

	current = find_or_create_node(&head, fd);
	buf = malloc(BUFFER_SIZE + 1);
	current->stash = read_operation(fd, buf, current->stash);
	if (current->stash == NULL || *current->stash == '\0')
	{
		free (buf);
		ft_remove_node_fd(&head, current);
		return (NULL);
	}
	line = extract_line(&current->stash);
	free (buf);
	return (line);
}
