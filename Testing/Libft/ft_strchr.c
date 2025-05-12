/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 07:29:01 by wheino            #+#    #+#             */
/*   Updated: 2025/05/02 17:39:33 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Locates the first occurrence of c in the string pointed to by s.
 * @param s: Pointer to the string to search.
 * @param c: The character to locate.
 * @return	A pointer to the first occurrence of c in the string s, or NULL if
 * * 		the character is not found.
 * * 		If s is NULL, the function returns NULL.
 * * 		If s is an empty string, the function returns NULL.
 */

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == c)
		return ((char *)&s[i]);
	return (NULL);
}
