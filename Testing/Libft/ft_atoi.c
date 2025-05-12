/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 11:40:18 by wheino            #+#    #+#             */
/*   Updated: 2025/04/30 11:19:30 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts a string to an integer.
 * @param nptr: The string to convert to an integer.
 * @return The converted integer.
 */

int	ft_atoi(const char *nptr)
{
	int	i;
	int	is_neg;
	int	result;

	i = 0;
	is_neg = 0;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] <= 13 && nptr[i] >= 7))
		i++;
	if ((nptr[i] == '-') || (nptr[i] == '+'))
	{
		if (nptr[i] == '-')
			is_neg++;
		i++;
	}
	while (ft_isdigit(nptr[i]))
	{
		result = 10 * result + (nptr[i] - '0');
		i++;
	}
	if (is_neg == 1)
		return (result * -1);
	return (result);
}
