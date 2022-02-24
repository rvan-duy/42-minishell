/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_protect.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 13:56:20 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/23 17:09:17 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

void	*ft_protect(void *ptr)
{
	if (ptr != NULL)
		return (ptr);
	ft_putstr_fd("Malloc failed\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
	return (NULL);
}
