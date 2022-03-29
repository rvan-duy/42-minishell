/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_utoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/26 15:25:07 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/28 11:42:44 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

char	*ft_utoa(uint64_t nbr)
{
	uint8_t	i;
	char	*res;

	i = ft_nbrlen_u(nbr, 10);
	res = ft_calloc(i + 1, sizeof(char));
	while (i != 0)
	{
		i--;
		res[i] = '0' + (nbr % 10);
		nbr /= 10;
	}
	return (res);
}
