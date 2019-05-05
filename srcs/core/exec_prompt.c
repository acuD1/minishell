/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:16:16 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/05 14:51:14 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**token_parser(char *line)
{
	char	**tokens;

	tokens = ft_strsplit(line, ' ');
	return (tokens);
}

void		exec_prompt(t_core *shell)
{
	char	**tokens;
	char	*line;
	int		status;

	status = 1;
	credit(shell);
	while (status)
	{
		init_prompt();
		if (!(status = get_next_line(STDIN_FILENO, &line)))
			break ;
		tokens = token_parser(line);
		if (!(exec_process(shell, tokens)) || shell->flag.exit)
		{
			free_tab(tokens);
			free(line);
			return ;
		}
		// LOGGER
		helper(shell, line, tokens);
		// LOGGER
		free_tab(tokens);
		free(line);
	}
	free(line);
}
