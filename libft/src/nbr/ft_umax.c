/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_umax.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 14:24:13 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/01/27 14:27:02 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

size_t	ft_umax(size_t a, size_t b)
{
	if (a > b)
		return (a);
	return (b);
}
