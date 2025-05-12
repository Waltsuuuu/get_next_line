/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 07:53:41 by wheino            #+#    #+#             */
/*   Updated: 2025/05/02 22:45:49 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the last occurrence of c in the string pointed to by s.
 * @param s: Pointer to the string to search.
 * @param c: The character to locate.
 * @return	A pointer to the last occurrence of c in the string s, or NULL if
 * * 		the character is not found.
 * * 		If s is NULL, the function returns NULL.
 * * 		If s is an empty string, the function returns NULL.
 */

char	*ft_strrchr(const char *s, int c)
{
	int	i;

	i = ft_strlen((char *)s);
	while (i >= 0)
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i--;
	}
	return (NULL);
}
