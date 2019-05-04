/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:36:24 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/04 10:14:35 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern char **environ;

char	**token_parser(char *line)
{
	char	**tokens;

	tokens = ft_strsplit(line, ' ');
	return (tokens);
}

int		exec_process(t_core *shell, char **tokens)
{
	(void)shell;
	pid_t	child_pid;
	int		status;

	child_pid = fork();
	shell->child_pid = child_pid;
	if (child_pid < 0)
	{
		ft_mprintf(STDERR_FILENO, "%sFork failed !\n%s",
			C_R, C_X);
		exit(1);
	}
	if (child_pid == 0)
	{
		if (execve(tokens[0], tokens, environ) < 0)
		{
			ft_mprintf(STDERR_FILENO, "%sExecve failed !\n%s",
				C_R, C_X);
			exit(1);
		}
	}
	else
		waitpid(child_pid, &status, WUNTRACED);
	return (0);
}

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
		exec_process(shell, tokens);
		// LOGGER
		helper(shell, line, tokens);
		// LOGGER
		free_tokens(tokens);
		free(line);
	}
	free(line);
}
