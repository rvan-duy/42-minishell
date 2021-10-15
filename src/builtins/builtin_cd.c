/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 11:14:09 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/15 13:52:59 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "envp.h"
#include "safe.h"
#include <unistd.h>
#include <stdlib.h>

int	builtin_cd(t_cmd_node *nodes, char *envp[])
{
	char	*home;

	if (nodes->argv[1] == NULL || nodes->argv[1][0] == '~')
	{
		if (envp_get_var("HOME", envp, &home) == FAILURE)
			return (EXIT_FAILURE);
		safe_chdir(home);
	}
	else
		safe_chdir(nodes->argv[1]);
	return (EXIT_SUCCESS);
}
