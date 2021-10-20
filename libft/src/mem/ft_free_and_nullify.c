/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_free_and_nullify.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: marius <marius@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/09/26 20:38:11 by marius        #+#    #+#                 */
/*   Updated: 2021/10/18 11:41:21 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_free_and_nullify(void *ptr)
{
	void	**p;

	p = (void **)ptr;
	free(*p);
	*p = NULL;
	return (NULL);
}
