/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:08:04 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/09 11:41:18 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_list *env)
{
	t_list	*tmp;

	while (env)
	{
		ft_strdel(&((t_db*)(env->content))->symbol);
		ft_strdel(&((t_db*)(env->content))->value);
		free(env->content);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

void	free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
	{
		ft_strdel(&tab[i]);
		i++;
	}
	free(tab);
}

void	free_prompt(t_core *shell, char **tokens, char *line)
{
	ft_strdel(&shell->bin);
	free_tab(tokens);
	ft_strdel(&line);
}

void	free_core(t_core *shell)
{
	free_list(shell->env);
}
