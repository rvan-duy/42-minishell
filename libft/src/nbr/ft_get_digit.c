/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_get_digit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/06 15:00:20 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/09/06 15:17:11 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_get_digit(int num, int pos, int base)
{
	while (pos > 0)
	{
		num /= base;
		pos--;
	}
	return (num % base);
}
