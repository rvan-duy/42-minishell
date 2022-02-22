/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_protect.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 13:56:20 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/22 11:26:53 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_protect(void *ptr)
{
	if (ptr != NULL)
		return (ptr);
	ft_putstr_fd("Malloc failed\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
	return (NULL);
}
