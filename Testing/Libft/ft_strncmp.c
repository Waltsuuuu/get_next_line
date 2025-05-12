/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:00:32 by wheino            #+#    #+#             */
/*   Updated: 2025/05/02 22:16:40 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compares the first n bytes of two strings s1 and s2.
 * @param s1: Pointer to the first string.
 * @param s2: Pointer to the second string.
 * @param n: Number of bytes to compare.
 * @return 0 if the first n bytes of s1 and s2 are equal,
 *         a positive value if s1 is greater than s2,
 *         a negative value if s1 is less than s2.
 */

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (!(s1[i] == s2[i]))
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
