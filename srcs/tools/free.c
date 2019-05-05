/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 14:08:04 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/05 15:24:47 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_list(t_list *env)
{
	t_list	*tmp;

	while (env)
	{
		free(ENV_DB->symbol);
		free(ENV_DB->value);
		free(env->content);
		tmp = env;
		env = env->next;
		free(tmp);
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}
