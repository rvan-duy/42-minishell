/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 11:14:09 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/14 11:51:55 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

int	builtin_cd(t_cmd_node *nodes)
{
	if (nodes->argv[1] == NULL || nodes->argv[1][0] == '~')
	{
		if (chdir(getenv("HOME")) < 0)
		{
			perror("cd");
			return (EXIT_FAILURE);
		}
	}
	else if (chdir(nodes->argv[1]) < 0)
	{
		perror("cd");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
