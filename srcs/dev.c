/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:36:24 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/26 16:17:19 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int8_t	exp_shifter(t_core *shell, char *tokens, char *tmp)
{
	t_list *env;
	t_list *var;

	env = shell->env;
	var = shell->var;
	while (var)
	{
		if (ft_strequ(((t_db*)(var->content))->symbol, tmp) == TRUE)
		{
			ft_strdel(&tokens);
			tokens = ft_strdup(((t_db*)(var->content))->value);
			return (SUCCESS);
		}
		var = var->next;
	}
	while (env)
	{
		if (ft_strequ(((t_db*)(env->content))->symbol, tmp) == TRUE)
		{
			ft_strdel(&tokens);
			tokens = ft_strdup(((t_db*)(env->content))->value);
			return (SUCCESS);
		}
		env = env->next;
	}
	return (FAILURE);






}
