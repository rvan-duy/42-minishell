/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ispunct.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/28 15:20:21 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/03/28 11:42:40 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_ispunct(int c)
{
	return (ft_isprint(c) && !ft_isalnum(c));
}
