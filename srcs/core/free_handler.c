/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:08:04 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/10 15:18:03 by arsciand         ###   ########.fr       */
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

void	free_prompt(t_core *shell, char ***tokens, char *line)
{
	ft_strdel(&shell->bin);
	ft_free_tab(tokens);
	ft_strdel(&line);
}
