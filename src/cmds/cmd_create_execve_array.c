/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cmd_create_execve_array.c                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/08 19:19:24 by rvan-duy      #+#    #+#                 */
/*   Updated: 2022/02/08 19:31:33 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * Combines command and arguments into one array, terminal by NULL
 * @param command pointer to `char *`
 * @param arguments pointer to `char **`
 * @return A pointer to an combined array allocated with malloc() 
 * - NULL if command is NULL
 */
char	**cmd_create_execve_array(char *command, char **arguments)
{
	char	**array;
	size_t	array_len;
	size_t	i;

	if (command == NULL)
		return (NULL);
	array_len = 1 + ft_array_len((void **)arguments);
	array = ft_calloc(array_len + 1, sizeof(char *));
	if (array == NULL)
		exit(EXIT_FAILURE);
	array[0] = ft_strdup(command);
	if (array[0] == NULL)
		exit(EXIT_FAILURE);
	free(command);
	i = 1;
	while (i < array_len)
	{
		array[i] = ft_strdup(arguments[i - 1]);
		if (array[i] == NULL)
			exit(EXIT_FAILURE);
		i++;
	}
	return (array);
}
