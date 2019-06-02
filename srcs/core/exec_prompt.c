/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:16:16 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/02 14:02:22 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

uint8_t	set_exp_var(t_core *shell, char **tokens)
{
	size_t	i;

	i = 0;
	if (ft_strequ(tokens[0], "env") == TRUE)
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
			//logger(shell, NULL, NULL);
			if (shell->exit == TRUE)
				return ;
			continue ;
		}
		exec_process(shell, shell->env, tokens);
		//logger(shell, line, tokens);
		free_prompt(shell, &tokens, line);
	}
	ft_strdel(&line);
}
