/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:16:16 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/27 11:21:57 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

static void		update_env(t_core *shell)
{
	t_list	*env;
	int		tmp_shlvl;

	tmp_shlvl = 0;
	env = shell->env;
	while (env)
	{
		if (ft_strequ(((t_db*)(env->content))->symbol, "SHLVL") == TRUE)
		{
			tmp_shlvl = ft_atoi(((t_db*)(env->content))->value);
			ft_strdel(&((t_db*)(env->content))->value);
			((t_db*)(env->content))->value = ft_itoa(tmp_shlvl + 1);
			return ;
		}
		env = env->next;
	}
}

static uint8_t	set_exp_var(t_core *shell, char **tokens)
{
	size_t	i;

	i = 0;
	builtins_parser(shell, tokens[0]);
	if (shell->builtin ^ NO_BUILTIN)
		return (FALSE);
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '='))
		{
			ft_lstpushback(&shell->var,
				ft_lstnew(fetch_db(&shell->db, tokens[i]), sizeof(t_db)));
			logger(shell, NULL, tokens);
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void			exec_prompt(t_core *shell)
{
	char	**tokens;
	char	*line;

	tokens = NULL;
	line = NULL;
	credit(shell);
	update_env(shell);
	while (shell->prompt)
	{
		init_prompt();
		if (!(shell->prompt = get_next_line(STDIN_FILENO, &line)))
			break ;
		if (get_tokens(shell, line, &tokens) != SUCCESS
			|| set_exp_var(shell, tokens) == TRUE
			|| exec_builtins(shell, tokens) == SUCCESS)
		{
			free_prompt(shell, &tokens, line);
			if (shell->exit == TRUE)
				exit_handler(shell, shell->exit_value);
			continue ;
		}
		exec_process(shell, shell->env, tokens);
		free_prompt(shell, &tokens, line);
	}
	ft_strdel(&line);
}
