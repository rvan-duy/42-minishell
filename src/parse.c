/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/10/14 11:47:06 by mvan-wij      #+#    #+#                 */
/*   Updated: 2021/10/19 16:41:44 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "utilities.h"
#include "structs.h"
#include "libft.h"
#include <stdlib.h>

int	count_args(char *part)
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
	//TODO: split on pipe and redirect
	int		i;
	int		count;
	char	**args;
	char	*after;

	count = count_args(cmd);
	if (count < 0)
		return (NULL);
	args = malloc((count + 1) * sizeof(char *));
	if (args == NULL)
		return (NULL);
	i = 0;
	while (i < count)
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
	if ((*node)->argv[0] != NULL && (*node)->cmd == NULL)
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
 * if FAILURE is returned the list of nodes have to be freed manually
 */
t_status	extract_pipes(char **args, t_cmd_node **node)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (args[i] != NULL)
	{
		if (ft_memcmp(args[i], "|", 2) == 0)
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

t_status	free_piped_nodes(t_cmd_node **node)
{
	t_cmd_node	*n;
	t_cmd_node	*next;

	n = *node;
	while (n != NULL)
	{
		ft_free_arr_dim(&n->argv, 2);
		ft_free_and_nullify(&n->cmd);
		next = n->pipe_to;
		free(n);
		n = next;
	}
	*node = NULL;
	return (FAILURE);
}

t_bool	is_redirect(char *str)
{
	return (ft_strncmp(str, "<", 2) == 0 || ft_strncmp(str, ">", 2) == 0
		|| ft_strncmp(str, "<<", 3) == 0 || ft_strncmp(str, ">>", 3) == 0);
}

int	count_redirects(char **args)
{
	int		i;
	int		count;
	t_bool	was_redirect;

	was_redirect = false;
	count = 0;
	i = 0;
	while (args[i] != NULL)
	{
		if (is_redirect(args[i]))
		{
			if (was_redirect)
				return (-1);
			was_redirect = true;
			count++;
		}
		else
			was_redirect = false;
		i++;
	}
	if (was_redirect)
		return (-1);
	return (count);
}

void	set_redirects(t_cmd_node *node)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (node->argv[i] != NULL)
	{
		if (is_redirect(node->argv[i]))
		{
			if (node->argv[i][1] == '>')
				node->files[j]->e_type = HEREDOC_OUT;
			else if (node->argv[i][1] == '<')
				node->files[j]->e_type = HEREDOC_IN;
			else if (node->argv[i][0] == '>')
				node->files[j]->e_type = OUT;
			else if (node->argv[i][0] == '<')
				node->files[j]->e_type = IN;
			node->files[j]->file_name = node->argv[i + 1];
			j++;
			i++;
		}
		i++;
	}
}

void	set_argv(t_cmd_node *node)
{
	int		i;
	int		j;

	j = 0;
	i = 0;
	while (node->argv[i] != NULL)
	{
		if (is_redirect(node->argv[i]))
		{
			free(node->argv[i]);
			i++;
		}
		else
		{
			node->argv[j] = node->argv[i];
			j++;
		}
		i++;
	}
	node->argv[j] = NULL;
}

t_files	**init_redirects(t_cmd_node *n, int count)
{
	int	i;

	if (count < 0)
		return (NULL);
	n->files = malloc((count + 1) * sizeof(t_files *));
	if (n->files == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		n->files[i] = malloc(sizeof(t_files));
		if (n->files[i] == NULL)
			return (ft_free_arr_dim(&n->files, 2));
		i++;
	}
	n->files[i] = NULL;
	return (n->files);
}

t_status	extract_redirects(t_cmd_node **node)
{
	t_cmd_node	*n;
	int			count;

	n = *node;
	while (n != NULL)
	{
		count = count_redirects(n->argv);
		if (init_redirects(n, count) == NULL)
			return (FAILURE);
		set_redirects(n);
		set_argv(n);
		n = n->pipe_to;
	}
	return (SUCCESS);
}

/**
 * @param node use like: `t_cmd_node *node` => `&node`
 */
t_status	parse_thing(char *cmd, t_cmd_node **node)
{
	char	**args;

	args = parse_cmd(cmd);
	if (args == NULL)
		return (FAILURE);
	if (extract_pipes(args, node) == FAILURE)
	{
		free(args);
		return (free_piped_nodes(node));
	}
	free(args);
	return (extract_redirects(node));
}
