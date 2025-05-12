/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 12:39:03 by wheino            #+#    #+#             */
/*   Updated: 2025/05/12 12:26:37 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Appends the string src to the end of dst. It will append at most
 * 		  dstsize - strlen(dst) - 1 characters from src, and null-terminate
 * 		  the result.
 * @param dst: The destination string to which src is appended.
 * @param src: The source string to append to dst.
 * @param dstsize: The size of the destination buffer.
 * @return The total length of the string that would have been created if
 *         there was enough space in dst.
 */

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	src_len;
	size_t	dst_len;
	int		i;

	src_len = (size_t)ft_strlen((char *)src);
	dst_len = (size_t)ft_strlen(dst);
	if (dst_len >= dstsize)
		return (dstsize + src_len);
	i = 0;
	while ((src[i] != '\0' && (dst_len + i < dstsize - 1)))
	{	
		dst[i + dst_len] = src[i];
		i++;
	}
	dst[i + dst_len] = '\0';
	return (src_len + dst_len);
}
