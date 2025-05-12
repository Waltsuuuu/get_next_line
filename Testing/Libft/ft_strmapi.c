/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 15:38:34 by wheino            #+#    #+#             */
/*   Updated: 2025/05/12 12:26:51 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Applies the function f to each character of the string s,
 *        passing its index as the first argument.
 *        The result is stored in a new string, which is returned.
 * @param s: The string to iterate over.
 * @param f: The function to apply to each character.
 * @return A new string resulting from the successive applications of f.
 *         Returns NULL if the allocation fails or if s or f is NULL.
 */

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*str;
	int		i;

	if (!s || !f)
		return (NULL);
	str = malloc((ft_strlen((char *)s) + 1) * sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, ft_strlen((char *)s) + 1);
	i = 0;
	while (s[i] != '\0')
	{
		str[i] = f(i, s[i]);
		i++;
	}
	return (str);
}
