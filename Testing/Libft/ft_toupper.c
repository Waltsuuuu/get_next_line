/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 14:25:37 by wheino            #+#    #+#             */
/*   Updated: 2025/05/12 12:30:21 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * * @brief Converts a lowercase letter to its uppercase equivalent.
 * * If the character is not a lowercase letter, it is returned unchanged.
 * * @param c: The character to convert.
 * * @return The uppercase equivalent of the lowercase letter c,
 * *         or c if it is not a lowercase letter.
 */

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	else
		return (c);
}
