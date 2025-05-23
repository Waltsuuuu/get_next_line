/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 14:16:03 by wheino            #+#    #+#             */
/*   Updated: 2025/05/23 15:17:45 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# include <unistd.h>
# include <stdlib.h>

typedef struct s_fd_node
{
	int					fd;
	char				leftover[BUFFER_SIZE + 1];
	struct s_fd_node	*next;
}				t_fd_node;

size_t		ft_strlen(const char *src);
char		*ft_strchr(const char *s, int c);
char		*ft_strjoin(char const *s1, char const *s2);
size_t		ft_strlcpy(char *dst, const char *src, size_t dstsize);
char		*ft_strldup(const char *s, size_t len);
int			count_chars_to_newline(char *str);
char		*read_operation(int fd, char *buf, char *stash);
char		*nothing_to_return(char *buf, char *stash);
char		*extract_line(char **stash, char leftover[BUFFER_SIZE + 1]);
t_fd_node	*find_or_create_node(t_fd_node **head, int fd);
void		ft_remove_node_fd(t_fd_node **head, t_fd_node *current);
char		*get_next_line(int fd);

#endif