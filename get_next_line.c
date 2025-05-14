/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:15:23 by wheino            #+#    #+#             */
/*   Updated: 2025/05/14 15:14:18 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*stash;
	char		*temp_stash;
	char		*line;

	buf = malloc(5 + 1);
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
