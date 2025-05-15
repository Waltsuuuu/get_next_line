/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:16:03 by wheino            #+#    #+#             */
/*   Updated: 2025/05/15 19:02:28 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_fd_node
{
	int					fd;
	char				*stash;
	struct s_fd_node	*next;
}				t_fd_node;

size_t	ft_strlen(const char *src);
char	*ft_strchr(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strdup(const char *s);
char	*ft_strldup(const char *s, size_t len);
int		count_chars_to_newline(char *str);
char	*read_operation(int fd, char *buf, char *stash);
char	*nothing_to_return(char *buf, char *stash);
char	*extract_line(char *stash, char **updated_stash);
t_fd_node	*ft_lstnew_fd(int fd);
char	*get_next_line(int fd);

#endif