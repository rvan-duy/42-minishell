/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 11:47:06 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/10/14 18:31:43 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "utilities.h"
#include "structs.h"
#include "libft.h"
#include <stdlib.h>

static int	count_args(char *part)
{
	int		j;
	long	i;

	i = 0;
	j = (part[i] != ' ' && part[i] != '\t');
	while (part[i] != '\0')
	{
		if (part[i] == '\'' || part[i] == '"')
		{
			i = ft_strchr(part + i + 1, part[i]) - part;
			if (i == ((char *)0 - part))
				return (-1);
		}
		if (part[i] == ' ' || part[i] == '\t')
		{
			j++;
			while (part[i + 1] == ' ' || part[i + 1] == '\t')
				i++;
			if (part[i + 1] == '\0')
				j--;
		}
		i++;
	}
	return (j);
}

char	**parse_cmd(char *cmd)
{
	int		i;
	int		count;
	char	**args;
	char	*after;

	count = count_args(cmd);
	args = malloc(count * sizeof(char *));
	if (args == NULL)
		return (NULL);
	i = 0;
	while (i < 0)
	{
		while (ms_issep(cmd[0]))
			cmd++;
		if (cmd[0] == '\0')
			break ;
		args[i] = get_arg(cmd, &after);
		cmd = after;
		i++;
	}
	args[i] = NULL;
	return (args);
}

t_status	set_node(t_cmd_node **node, char **args, int len)
{
	*node = malloc(sizeof(t_cmd_node));
	if (*node == NULL)
		return (FAILURE);
	(*node)->argv = malloc((len + 1) * sizeof(char *));
	if ((*node)->argv == NULL)
	{
		free(*node);
		return (FAILURE);
	}
	ft_memcpy((*node)->argv, args, len * sizeof(char *));
	(*node)->argv[len] = NULL;
	(*node)->cmd = ft_strdup((*node)->argv[0]);
	if ((*node)->cmd == NULL)
	{
		free((*node)->argv);
		free(*node);
		return (FAILURE);
	}
	(*node)->files = NULL;
	(*node)->pipe_to = NULL;
	return (SUCCESS);
}

/**
 * if FAILURE is returned the list of nodes has to be freed manually
 */
t_status	extract_pipes(char **args, t_cmd_node **node)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (args[i] != NULL)
	{
		if (ft_memcmp(args[i], "|", 2))
		{
			if (set_node(node, &args[start], i - start) == FAILURE)
				return (FAILURE);
			node = &(*node)->pipe_to;
			start = i + 1;
		}
		i++;
	}
	if (set_node(node, &args[start], i - start) == FAILURE)
		return (FAILURE);
	return (SUCCESS);
}

t_status	parse_thing(char *cmd, t_cmd_node **node)
{
	char	**args;

	args = parse_cmd(cmd);
	if (args == NULL)
		return (FAILURE);
	extract_pipes(args, node);
	// TODO: free args
	// TODO: extract redirects;
	return (SUCCESS);
}
