/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:36:24 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/03 15:11:30 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**token_parser(char *line)
{
	char	**tokens;

	tokens = ft_strsplit(line, ' ');
	return (tokens);
}

/*
void	exec_process(t_core *shell)
{
	pid_t	child_pid;

	child_pid = fork();
	if (child_pid < 0)
	{
		return(exit_status)
	}

}
*/
void	exec_prompt(t_core *shell)
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
//		exec_process(env, tokens);
		// LOGGER
		helper(shell, line, tokens);
		// LOGGER
		free_tokens(tokens);
		free(line);
	}
	free(line);
}
