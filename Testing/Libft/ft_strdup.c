/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:24:28 by wheino            #+#    #+#             */
/*   Updated: 2025/05/02 20:50:35 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Duplicates the string s by allocating memory for a new string
 * 	   	  and copying the contents of s into it.
 * @param s: The string to duplicate.
 * @return A pointer to the newly allocated string, or NULL if the allocation
 * 	   	   fails.
 */

char	*ft_strdup(const char *s)
{
	char	*new_str;
	size_t	len;

	len = ft_strlen((char *)s) + 1;
	new_str = malloc(len * sizeof(char));
	if (!new_str)
		return (NULL);
	ft_memcpy(new_str, s, len);
	return (new_str);
}
