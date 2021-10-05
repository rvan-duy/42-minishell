/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa_basei_bonus.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/31 11:11:59 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/03/11 13:36:18 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

char	*ft_itoa_basei(int64_t nbr, uint8_t base, int cap)
{
	char	*basechars;
	uint8_t	i;
	char	*val;

	if (base < 2 || base > 36)
		return (NULL);
	basechars = malloc((base + 1) * sizeof(char));
	if (basechars == NULL)
		return (NULL);
	i = 0;
	while (i < base)
	{
		if (i < 10)
			basechars[i] = (char)('0' + i);
		else if (cap)
			basechars[i] = (char)('A' + i - 10);
		else
			basechars[i] = (char)('a' + i - 10);
		i++;
	}
	basechars[i] = '\0';
	val = ft_itoa_base(nbr, basechars);
	free(basechars);
	return (val);
}
