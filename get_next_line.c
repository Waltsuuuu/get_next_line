/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:15:23 by wheino            #+#    #+#             */
/*   Updated: 2025/05/14 15:48:24 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*stash;
	char		*line;

	buf = malloc(BUFFER_SIZE + 1);
	if (stash == NULL)
		stash = ft_strdup("");
	stash = read_operation(fd, buf, stash);
	if (stash == NULL || *stash == '\0')
	{
		free (buf);
		free (stash);
		stash = NULL;
		return (NULL);
	}
	line = extract_line(stash, &stash);
	free (buf);
	return (line);
}
