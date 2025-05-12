/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:48:01 by wheino            #+#    #+#             */
/*   Updated: 2025/05/12 12:29:55 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * * @brief Converts an uppercase letter to its lowercase equivalent.
 * * If the character is not an uppercase letter, it is returned unchanged.
 * * * @param c: The character to convert.
 * * @return The lowercase equivalent of the uppercase letter c,
 * *         or c if it is not an uppercase letter.
 */

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
	else
		return (c);
}
