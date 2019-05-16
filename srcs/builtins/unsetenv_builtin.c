/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unsetenv_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 12:39:44 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/16 14:42:11 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_node(t_list *node)
{
	ft_strdel(&((t_db*)(node->content))->symbol);
	ft_strdel(&((t_db*)(node->content))->value);
	free(node->content);
	free(node);
}

int8_t	unsetenv_builtin(t_list **env, char **tokens)
{
	t_list	*node;
	t_list	*prev;
	t_list	*next;
	int8_t	status;

	node = *env;
	prev = NULL;
	status = FAILURE;
	while (node != NULL)
	{
		next = node->next;
		if (ft_strequ(((t_db*)(node->content))->symbol, tokens[1]) == TRUE)
		{
			free_env_node(node);
			if (prev)
				prev->next = next;
			else
				*env = next;
			status = SUCCESS;
		}
		else
			prev = node;
		node = next;
	}
	return (status);
}
