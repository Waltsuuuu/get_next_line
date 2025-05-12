/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 13:22:58 by wheino            #+#    #+#             */
/*   Updated: 2025/04/30 13:54:46 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Writes the character c to the file descriptor fd.
 * @param c: The character to write.
 * @param fd: The file descriptor to write to.
 * @return None.
 *         If fd is not valid, the function does nothing.
 */

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
