/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_nbrlen_u.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/24 16:50:36 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/03/11 13:40:28 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>

uint8_t	ft_nbrlen_u(uint64_t nbr, uint64_t base)
{
	uint8_t		i;

	i = 1;
	while (nbr / base != 0)
	{
		nbr /= base;
		i++;
	}
	return (i);
}
