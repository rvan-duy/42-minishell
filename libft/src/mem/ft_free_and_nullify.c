/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_and_nullify.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: marius <marius@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/26 20:38:11 by marius        #+#    #+#                 */
/*   Updated: 2021/09/29 11:46:18 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_free_and_nullify(void **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}
