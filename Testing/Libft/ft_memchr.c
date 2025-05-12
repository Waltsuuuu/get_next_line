/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:23:37 by wheino            #+#    #+#             */
/*   Updated: 2025/04/30 12:36:09 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the first occurrence of c (converted to an unsigned char)
 * 			in the initial n bytes of the string pointed to by s.
 * @param s: Pointer to the memory area to search.
 * @param c: The character to locate.
 * @param n: The number of bytes to search.
 * @return A pointer to the first occurrence of c in the string s, or NULL if
 * 			the character is not found within the first n bytes.
 * 			If n is zero, the function returns NULL.
 */

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t		i;
	const char	*str;

	str = (const char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == (unsigned char)c)
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}
