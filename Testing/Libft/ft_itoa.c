/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wheino <wheino@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 11:09:21 by wheino            #+#    #+#             */
/*   Updated: 2025/05/06 11:29:21 by wheino           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Converts an integer to a string representation.
 * @param n: The integer to convert.
 * @return A pointer to the string representation of the integer.
 */

static char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

static char	*rev_str(char *str)
{
	int		start;
	int		end;
	char	temp;

	start = 0;
	end = ft_strlen(str) - 1;
	while (start < end)
	{
		temp = str[start];
		str[start] = str[end];
		str[end] = temp;
		start++;
		end--;
	}
	return (str);
}

int	count_digits(int n)
{
	int	digits;

	digits = 0;
	if (n == INT_MIN)
		return (10);
	while (n > 9)
	{
		n = n / 10;
		digits++;
	}
	if (n <= 9)
	{
		digits++;
	}
	return (digits);
}

char	*ft_itoa(int n)
{
	char	*result;
	int		i;
	int		sign;

	i = 0;
	sign = (n < 0);
	result = malloc(count_digits(n) * sizeof(char) + sign + 1);
	if (n == INT_MIN)
	{
		result = ft_strcpy(result, "-2147483648");
		return (result);
	}
	if (sign)
		n = n * -1;
	while (n > 9)
	{
		result[i++] = (n % 10) + '0';
		n = n / 10;
	}
	result[i++] = n + '0';
	if (sign == 1)
		result[i++] = '-';
	result[i] = '\0';
	return (rev_str(result));
}
