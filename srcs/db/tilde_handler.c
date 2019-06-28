/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tilde_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:13:43 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/28 10:14:32 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		conv_home(t_core *shell, char **tokens, char *path, size_t i)
{
	t_list	*env;

	env = shell->env;
	shell->exp = 1;
	path = ft_strsub(tokens[i], 1, ft_strlen(tokens[i]));
	ft_strdel(&tokens[i]);
	while (env)
	{
		if (ft_strequ(((t_db*)(env->content))->symbol, "HOME") == TRUE)
			tokens[i] = ft_strjoinf(((t_db*)(env->content))->value,
							path, FREE_2);
		env = env->next;
	}
}

void		conv_pwd(t_core *shell, char **tokens, char *path, size_t i)
{
	t_list	*env;

	env = shell->env;
	shell->exp = 1;
	path = ft_strsub(tokens[i], 2, ft_strlen(tokens[i]));
	while (env)
	{
		if (tokens[i][1] == '-'
			&& ft_strequ(((t_db*)(env->content))->symbol,
			"OLDPWD") == TRUE)
		{
			ft_strdel(&tokens[i]);
			tokens[i] = ft_strjoinf(((t_db*)(env->content))->value,
							path, FREE_2);
		}
		if (tokens[i][1] == '+'
			&& ft_strequ(((t_db*)(env->content))->symbol,
			"PWD") == TRUE)
		{
			ft_strdel(&tokens[i]);
			tokens[i] = ft_strjoinf(((t_db*)(env->content))->value,
							path, FREE_2);
		}
		env = env->next;
	}
}
