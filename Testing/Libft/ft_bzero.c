/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 06:35:28 by wheino            #+#    #+#             */
/*   Updated: 2025/04/30 11:18:18 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
* @brief Sets the first n bytes of the memory area pointed to by s to zero.
* 
* @param s: Pointer to the memory area to be set to zero.
* @param n: Number of bytes to set to zero.
* @return Pointer to the memory area s.
*/

void	*ft_bzero(void *s, size_t n)
{
	unsigned char	*ptr;

	ptr = (unsigned char *)s;
	while (n--)
		*ptr++ = 0;
	return (s);
}
