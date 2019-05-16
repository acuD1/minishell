/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setenv_builtin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 14:59:31 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/16 16:08:15 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "unistd.h"

static uint8_t	setenv_builtin_usage(void)
{
	ft_putendl_fd("usage: setenv [symbol] [value] [int]", STDERR_FILENO);
	return (SUCCESS);
}

int8_t			setenv_builtin(t_core *shell, t_list **env, char **tokens)
{
	t_list	*node;

	node = *env;
	if (ft_tablen(tokens) != 4 || !(ft_isdigit(tokens[3][0])))
		return (setenv_builtin_usage());
	while (node)
	{
		if (ft_strequ(tokens[1], ((t_db*)(node->content))->symbol) == TRUE)
		{
			if (tokens[3][0] == '0')
				return (FAILURE);
			ft_strdel(&((t_db*)(node->content))->value);
			((t_db*)(node->content))->value = ft_strdup(tokens[2]);
			return (SUCCESS);
		}
		node = node->next;
	}
	shell->db.symbol = ft_strdup(tokens[1]);
	shell->db.value = ft_strdup(tokens[2]);
	ft_lstpushback(&shell->env, ft_lstnew(&shell->db, sizeof(t_db)));
	return (SUCCESS);
}
