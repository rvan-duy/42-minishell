/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_min.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/27 14:24:13 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/01/27 14:26:40 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

ssize_t	ft_min(ssize_t a, ssize_t b)
{
	if (a < b)
		return (a);
	return (b);
}
