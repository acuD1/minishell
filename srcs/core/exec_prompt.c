/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:16:16 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/11 15:42:44 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

uint8_t	set_exp_var(t_core *shell, char **tokens)
{
	t_db	var_db;
	size_t	i;

	i = 0;
	var_db = shell->db;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '='))
		{
			ft_lstpushback(&shell->var,
				ft_lstnew(fetch_db(&var_db, tokens[i]), sizeof(t_db)));
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

void	exec_prompt(t_core *shell)
{
	char	**tokens;
	char	*line;

	tokens = NULL;
	line = NULL;
	credit(shell);
	while (shell->status)
	{
		init_prompt();
		if (!(shell->status = get_next_line(STDIN_FILENO, &line)))
			break ;
		if (get_tokens(shell, line, &tokens) != SUCCESS
			|| set_exp_var(shell, tokens) == TRUE
			|| exec_builtins(shell, tokens) == SUCCESS)
		{
			free_prompt(shell, &tokens, line);
			if (shell->exit == TRUE)
				return ;
			continue ;
		}
		exec_process(shell, tokens);
		logger(shell, line, tokens);
		free_prompt(shell, &tokens, line);
	}
	ft_strdel(&line);
}
