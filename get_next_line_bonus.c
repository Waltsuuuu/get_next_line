/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:15:23 by wheino            #+#    #+#             */
/*   Updated: 2025/05/15 19:02:08 by wheino           ###   ########.fr       */
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

char	*extract_line(char *stash, char **updated_stash)
{
	char	*line;
	char	*newline_i_ptr;
	int	newline_index;

	newline_i_ptr = ft_strchr(stash, '\n');
	if (newline_i_ptr)
	{
		newline_index = 0;
		while (stash[newline_index] != '\n')
			newline_index++;
		line = ft_strldup(stash, newline_index + 1);
		*updated_stash = ft_strdup(newline_i_ptr + 1);
	}
	else
	{
		line = ft_strdup(stash);
		*updated_stash = NULL;
	}
	free(stash);
	return (line);
}

t_fd_node	*ft_lstnew_fd(int fd)
{
	t_fd_node	*new_node;

	new_node = malloc(sizeof(t_fd_node));
	if (!new_node)
		return (NULL);
	new_node->fd = fd;
	new_node->stash = ft_strdup("");
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstdelone_fd(t_fd_node *lst, void (*del) (void *))
{
	if (lst == NULL || del == NULL)
		return ;
	del(lst->stash);
	free(lst);
}

char	*get_next_line(int fd)
{
	static t_fd_node	*head;
	t_fd_node			*current;
	t_fd_node			*previous;
	char				*buf;
	char				*line;

	if (!head)
	{
		head = ft_lstnew_fd(fd);
		current = head;
	}
	else
	{
		current = head;
		while (current != NULL)
		{
			if (current->fd == fd)
				break ;
			if (!current->next)
			{
				current->next = ft_lstnew_fd(fd);
				current = current->next;
				break ;
			}
			current = current->next;
		}
	}
	buf = malloc(BUFFER_SIZE + 1);
	current->stash = read_operation(fd, buf, current->stash);
	if (current->stash == NULL || *current->stash == '\0')
	{
		free (buf);
		if (head == current)
		{
			head = head->next;
			ft_lstdelone_fd(current, free);
		}
		else
		{
			previous = head;
			while (previous && previous->next != current)
				previous = previous->next;
			if (previous)
			{
				previous->next = current->next;
				ft_lstdelone_fd(current, free);
			}
		}
		return (NULL);
	}
	line = extract_line(current->stash, &current->stash);
	free (buf);
	return (line);
}
