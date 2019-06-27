/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_shifter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/27 09:12:41 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/27 09:19:35 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int8_t	shift_exp_tokens(t_list *env, t_list *var, char **tokens, char *tmp)
{
	while (var)
	{
		if (ft_strequ(((t_db*)(var->content))->symbol, tmp) == TRUE)
		{
			ft_strdel(&tmp);
			ft_strdel(tokens);
			*tokens = ft_strdup(((t_db*)(var->content))->value);
			return (SUCCESS);
		}
		var = var->next;
	}
	while (env)
	{
		if (ft_strequ(((t_db*)(env->content))->symbol, tmp) == TRUE)
		{
			ft_strdel(&tmp);
			ft_strdel(tokens);
			*tokens = ft_strdup(((t_db*)(env->content))->value);
			return (SUCCESS);
		}
		env = env->next;
	}
	ft_strdel(&tmp);
	return (FAILURE);
}

int8_t	exp_shifter(t_core *shell, char **tokens)
{
	t_list	*env;
	t_list	*var;
	char	*tmp;

	env = shell->env;
	var = shell->var;
	tmp = ft_strsub(*tokens, 1, ft_strlen(*tokens));
	return (shift_exp_tokens(env, var, tokens, tmp));
}
