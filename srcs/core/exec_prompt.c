/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:16:16 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/08 17:44:24 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_prompt(t_core *shell, char **tokens, char *line)
{
	ft_strdel(&shell->bin_path);
	free_tab(tokens);
	ft_strdel(&line);
}

void		exec_prompt(t_core *shell)
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
		tokens = ft_strsplit(line, ' ');
		if ((exec_builtins(shell, tokens)) == SUCCESS)
		{
			free_prompt(shell, tokens, line);
			if (shell->flag.exit)
				return ;
			continue ;
		}
		exec_process(shell, tokens);
		// LOGGER
		helper(shell, line, tokens);
		// LOGGER
		free_prompt(shell, tokens, line);
	}
	ft_strdel(&line);
}
