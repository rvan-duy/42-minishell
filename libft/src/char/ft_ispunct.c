/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ispunct_bonus.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 15:20:21 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/06/22 13:01:44 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ispunct(int c)
{
	return (ft_isprint(c) && !ft_isalnum(c));
}
