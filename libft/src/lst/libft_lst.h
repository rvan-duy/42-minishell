/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libft_lst.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mvan-wij <mvan-wij@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/07/27 14:55:06 by mvan-wij      #+#    #+#                 */
/*   Updated: 2022/02/25 14:27:36 by mvan-wij      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LST_H
# define LIBFT_LST_H

# include <stddef.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	*ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
int		ft_lstinsert(t_list **lst, t_list *new, unsigned int i);
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list	*ft_lstnew(void *content);
size_t	ft_lstsize(t_list *lst);
t_list	*ft_lstitem(t_list *lst, int i);
t_list	*ft_lstreverse(t_list **lst);
t_list	*ft_lstnew_front(void *content, t_list **lst);
t_list	*ft_lstnew_back(void *content, t_list **lst);
void	**ft_lst_to_arr(t_list *lst, void *end_indicator);
t_list	*ft_lst_from_arr(void **arr);

#endif
