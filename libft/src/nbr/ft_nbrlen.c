/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nbrlen.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 16:50:36 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/03/11 13:32:04 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

uint8_t	ft_nbrlen(int64_t nbr, uint32_t base)
{
	uint8_t		i;

	i = 1;
	if (nbr < 0)
		i++;
	while (nbr / base != 0)
	{
		nbr /= base;
		i++;
	}
	return (i);
}
