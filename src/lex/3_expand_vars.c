/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   3_expand_vars.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/02/16 14:47:07 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/22 12:02:44 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "lex.h"
#include "envp.h"
#include <stdlib.h>

char	*lookup_var(char *var_name, t_env_var *envp)
{
	if (ft_strcmp(var_name, "?") == 0)
		return (ft_itoa(g_exit_status));
	return (ft_protect(ft_strdup(env_get_var(var_name, envp)->name)));
}

char	*get_var_value(char *str, int *var_name_start, t_env_var *envp)
{
	const int	start = *var_name_start + 1;

	(*var_name_start)++;
	while (str[*var_name_start] != '\0'
		&& (ft_isalnum(str[*var_name_start]) || str[*var_name_start] == '_'))
		(*var_name_start)++;
	if (start == *var_name_start)
		return (ft_protect(ft_strdup("$")));
	return (lookup_var(\
		ft_protect(ft_substr(str, start, *var_name_start - start)), envp));
}

t_list	*get_replace_vars_parts(char *str, t_env_var *envp)
{
	t_list	*lst;
	int		i;
	int		start;

	lst = NULL;
	start = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			ft_protect(ft_lstnew_front(\
				ft_protect(ft_substr(str, start, i - start)), &lst));
			ft_protect(ft_lstnew_front(get_var_value(str, &i, envp), &lst));
			start = i;
		}
		else
			i++;
	}
	ft_protect(ft_lstnew_front(\
		ft_protect(ft_substr(str, start, i - start)), &lst));
	return (ft_lstreverse(&lst));
}

char	*replace_vars(char *str, t_env_var *envp)
{
	t_list	*lst;
	t_list	*copy;
	int		len;
	char	*out;

	lst = get_replace_vars_parts(str, envp);
	copy = lst;
	len = 0;
	while (copy != NULL)
	{
		len += ft_strlen(copy->content);
		copy = copy->next;
	}
	out = ft_protect(ft_calloc(len + 1, sizeof(char)));
	copy = lst;
	while (copy != NULL)
	{
		ft_strlcat(out, copy->content, (len + 1) * sizeof(char));
		copy = copy->next;
	}
	return (out);
}

void	expand_vars(t_list *tokens, t_env_var *envp)
{
	char			*tmp;
	t_heredoc_state	heredoc_state;

	heredoc_state = NOT_HEREDOC;
	while (tokens != NULL)
	{
		if (is_type(((t_token *)tokens->content)->type, DLESS))
			heredoc_state = WILL_HEREDOC;
		else if ((is_type(((t_token *)tokens->content)->type, UNQUOTED) \
			|| is_type(((t_token *)tokens->content)->type, DOUBLE_QUOTED)) \
			&& heredoc_state == NOT_HEREDOC)
		{
			tmp = replace_vars(((t_token *)tokens->content)->value, envp);
			free(((t_token *)tokens->content)->value);
			((t_token *)tokens->content)->value = tmp;
		}
		else if (is_type(((t_token *)tokens->content)->type, WORD)
			&& heredoc_state != NOT_HEREDOC)
			heredoc_state = IN_HEREDOC;
		else if (heredoc_state == IN_HEREDOC
			&& !is_type(((t_token *)tokens->content)->type, WORD))
			heredoc_state = NOT_HEREDOC;
		tokens = tokens->next;
	}
}
