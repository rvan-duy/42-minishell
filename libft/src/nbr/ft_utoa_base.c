/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_utoa_base_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 10:43:04 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/03/11 13:51:27 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

char	*ft_utoa_base(uint64_t nbr, char *basechars)
{
	size_t	base;
	uint8_t	i;
	char	*res;

	if (basechars == NULL)
		return (NULL);
	base = ft_strlen(basechars);
	if (base < 2)
		return (NULL);
	i = ft_nbrlen_u(nbr, base);
	res = ft_calloc(i + 1, sizeof(char));
	while (i != 0)
	{
		i--;
		res[i] = basechars[nbr % base];
		nbr /= base;
	}
	return (res);
}
