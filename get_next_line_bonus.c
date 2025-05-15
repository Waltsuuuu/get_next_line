/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:15:23 by wheino            #+#    #+#             */
/*   Updated: 2025/05/15 18:08:03 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_strldup(const char *s, size_t len)
{
	char	*new_str;

	new_str = malloc(len * sizeof(char) + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s, len);
	new_str[len] = '\0';
	return (new_str);
}

int	count_chars_to_newline(char *str)
{
	int	i;
	int	chars;

	i = 0;
	chars = 1;
	while (str[i] != '\n')
	{
		i++;
		chars++;
	}
	return (chars);
}

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
	char	*newline_index;

	newline_index = ft_strchr(stash, '\n');
	if (newline_index)
	{
		line = ft_strldup(stash, count_chars_to_newline(stash));
		*updated_stash = ft_strdup(newline_index + 1);
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

	//If no list exists, create the first node based on the passed in fd.
	if (!head)
	{
		head = ft_lstnew_fd(fd);
		current = head;
	}
	else //If a linked list exists, search for the node that represents the fd.
	{
		current = head; //Sets current to the start of the linked list.
		while (current != NULL)
		{
			if (current->fd == fd) //If the node is found, current points to the correct node
				break ;
			if (!current->next) //If no node is found, create a node for the fd.
			{
				current->next = ft_lstnew_fd(fd);
				current = current->next;
				break ;
			}
			current = current->next;
		}
	}
	//At this point current->stash should point to the stash of the fd.
	buf = malloc(BUFFER_SIZE + 1);
	current->stash = read_operation(fd, buf, current->stash);
	if (current->stash == NULL || *current->stash == '\0')
	{
		free (buf);
		if (head == current) //If the node we must delete is the head node.
		{
			head = head->next; //Set the node after the current head to be the new head
			ft_lstdelone_fd(current, free); //Delete the node
		}
		else
		{
			previous = head;
			while (previous && previous->next != current) //Prev will point to the node just before current
				previous = previous->next; //Traverse the linked list tuntil prev->next points to current.
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
