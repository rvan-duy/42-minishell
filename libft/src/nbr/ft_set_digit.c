/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_set_digit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/06 14:59:36 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/09/06 15:17:16 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft_nbr.h"

int	ft_set_digit(int num, int pos, int new_digit, int base)
{
	const int	prev_digit = ft_get_digit(num, pos, base);
	int			diff;

	diff = prev_digit - new_digit;
	while (pos > 0)
	{
		diff *= base;
		pos--;
	}
	return (num - diff);
}
