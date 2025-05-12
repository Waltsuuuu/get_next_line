/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 13:00:36 by wheino            #+#    #+#             */
/*   Updated: 2025/05/12 17:49:04 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include "libft.h"

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
			printf("New line found in stash\n");
		}
	}
	
	return stash;
}

int	main()
{
	char *line;
	int	fd = open("SomeText.txt", O_RDONLY);
	int i;

	i = 0;
	line = get_next_line(fd);
	printf("line = %s\n", line);
	// while (line != NULL)
	// {
	// 	printf("line[i] = %s\n", line);
	// 	free(line);
	// 	line = get_next_line(fd);
	// 	i++;
	// }
	close(fd);
	return 0;
}