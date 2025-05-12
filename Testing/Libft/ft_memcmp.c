/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 08:41:45 by wheino            #+#    #+#             */
/*   Updated: 2025/05/03 12:55:55 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Compares the first n bytes of two memory areas s1 and s2.
 * @param s1: Pointer to the first memory area.
 * @param s2: Pointer to the second memory area.
 * @param n: Number of bytes to compare.
 * @return  If s1 and s2 are equal, the function returns 0.
 * 			If s1 is less than s2, the function returns a negative value.
 * 			If s1 is greater than s2, the function returns a positive value.
 * 			If s1 and s2 are NULL, the function returns 0.
 * 			If n is zero, the function returns 0.
 */

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (!(str1[i] == str2[i]))
			return (str1[i] - str2[i]);
		i++;
	}
	return (0);
}
