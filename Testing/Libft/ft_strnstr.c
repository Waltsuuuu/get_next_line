/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 09:40:37 by wheino            #+#    #+#             */
/*   Updated: 2025/05/02 22:23:09 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * * @brief Locates the first occurrence of the substring little in the string
 * *        big, where not more than len characters are searched.
 * * @param big: The string to search in.
 * * @param little: The substring to search for.
 * * @param len: The maximum number of characters to search in big.
 * * @return A pointer to the first occurrence of little in big, or NULL if
 * *         little is not found within the first len characters of big.
 * *         If little is an empty string, the function returns a pointer to
 * *         the beginning of big.
 */

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (little == NULL || *little == '\0')
		return ((char *)big);
	while (big[i] != '\0' && i < len)
	{
		j = 0;
		while (big[i] == little[j] && i < len)
		{
			if (little[j + 1] == '\0')
				return ((char *)&big[i - j]);
			i++;
			j++;
		}
		i = i - j;
		i++;
	}
	return (NULL);
}
