/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_base_bonus.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 10:43:04 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/03/11 13:28:44 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

char	*ft_itoa_base(int64_t nbr, char *basechars)
{
	size_t	base;
	uint8_t	i;
	bool	is_neg;
	char	*res;

	if (basechars == NULL)
		return (NULL);
	base = ft_strlen(basechars);
	if (base < 2)
		return (NULL);
	is_neg = nbr < 0;
	i = ft_nbrlen(nbr, base);
	res = ft_calloc(i + 1, sizeof(char));
	while (i != is_neg)
	{
		i--;
		if (is_neg)
			res[i] = basechars[-nbr % base];
		else
			res[i] = basechars[nbr % base];
		nbr /= base;
	}
	if (is_neg)
		res[0] = '-';
	return (res);
}
