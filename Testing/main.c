/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:00:36 by wheino            #+#    #+#             */
/*   Updated: 2025/05/12 18:12:57 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"

char	*ft_strldup(const char *s, size_t len)
{
	char	*new_str;

	new_str = malloc(len * sizeof(char) + 1);
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s, len);
	new_str[len + 1] = '\0';
	return (new_str);
}

int	get_chars_to_newline(char *str)
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
	return(chars);
}

char *get_next_line(int fd)
{
	char *buf;
	static char *stash;
	static char *temp_stash;
	char *line;
	int bytes_read;
	int new_line;

	new_line = 0;
	buf = malloc(4);
	stash = malloc(4);
	while (new_line == 0)
	{
		bytes_read = read(fd, buf, 3);
		printf("Read %d bytes from fd '%d'.\n", bytes_read, fd);
		if(bytes_read > 0)
		{
			buf[bytes_read] = '\0';
			printf("null terminated buf.\n");
		}
		if (bytes_read <= 0)
		{
			free (buf);
			return(NULL);
		}
		temp_stash = ft_strjoin(stash, buf);
		free (stash);
		stash = temp_stash;
		printf("Stash = %s\n", stash);
		if (ft_strchr(stash, '\n') != NULL)
		{
			new_line++;
			printf("NEW LINE FOUND IN STASH\n");
			break ;
		}
	}
	line = ft_strldup(stash, get_chars_to_newline(stash));
	return line;
}

int	main()
{
	char *line;
	int	fd = open("SomeText.txt", O_RDONLY);
	int i;

	i = 0;
	line = get_next_line(fd);
	// printf("line = %s\n", line);
	while (line != NULL)
	{
		printf("\nRETURNED LINE[%d] = %s\n",i, line);
		free(line);
		line = get_next_line(fd);
		i++;
	}
	printf("\nRETURNED LINE[%d] = %s\n",i, line);
	close(fd);
	return 0;
}