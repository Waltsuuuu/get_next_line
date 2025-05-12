/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 16:11:11 by wheino            #+#    #+#             */
/*   Updated: 2025/05/02 22:50:42 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * * @brief Trims 'set' characters from the beginning and end of 's1'.
 * *        Allocates memory for the trimmed string.
 * *        The caller is responsible for freeing the allocated memory.
 * * @param s1: The string to be trimmed.
 * * @param set: The reference set of characters to trim.
 * * @return The trimmed string.
 * *         Returns NULL if the allocation fails.
 * *         If s1 or set is NULL, the function returns NULL.
 * *         If s1 is an empty string, the function returns an empty string.
 * *         If set is an empty string, the function returns a copy of s1.
 * *         If s1 contains only characters from set, the function returns an
 * *         empty string.
 */

char	*trim_string(const char *s1, char *trim, int start, int end)
{
	int	i;

	i = 0;
	while (start <= end)
	{
		trim[i] = s1[start];
		i++;
		start++;
	}
	trim[i] = '\0';
	return (trim);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		end;
	char	*trim;

	start = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	if (ft_strlen(s1) == 0)
		return (ft_strdup(""));
	while (ft_strchr(set, s1[start]) != NULL)
		start++;
	end = ft_strlen(s1) - 1;
	while (ft_strchr(set, s1[end]) != NULL)
		end--;
	if (start > end)
		return (ft_strdup(""));
	trim = malloc((end - start + 2) * sizeof(char));
	if (!trim)
		return (NULL);
	trim_string(s1, trim, start, end);
	return (trim);
}
