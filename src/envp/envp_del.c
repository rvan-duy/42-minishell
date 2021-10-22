/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   envp_del.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rvan-duy <rvan-duy@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/21 11:38:15 by rvan-duy      #+#    #+#                 */
/*   Updated: 2021/10/21 17:11:23 by rvan-duy      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "structs.h"
#include "libft.h"
#include <signal.h>

t_status	envp_del(char **envp, const char *name)
{
	const size_t	envp_len = ft_array_len((void **)envp);
	const size_t	name_len = ft_strlen(name);
	size_t			i;

	if (name == NULL)
		kill(0, SIGSEGV);
	i = 0;
	while (i < envp_len && ft_strncmp(envp[i], name, name_len) != 0)
		i++;
	if (i == envp_len)
		return (FAILURE);
	if (i != envp_len)
		ft_memmove(envp + i, envp + i + 1, (envp_len - i) * sizeof(char *));
	return (SUCCESS);
}
