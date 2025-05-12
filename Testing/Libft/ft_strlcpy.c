/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 10:38:41 by wheino            #+#    #+#             */
/*   Updated: 2025/05/02 21:57:25 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * * @brief Copies up to dstsize - 1 characters from the string src to dst,
 * 		  null-terminating the result if dstsize is not zero.
 * @param dst: The destination string to which src is copied.
 * @param src: The source string to copy from.
 * @param dstsize: The size of the destination buffer.
 * * @return The total length of the string that would have been created if
 * 			 there was enough space in dst.
 */

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (dstsize == 0)
		return (ft_strlen((char *)src));
	while (i < dstsize - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (ft_strlen((char *)src));
}
