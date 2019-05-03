/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:36:24 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/03 13:04:02 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**token_parser(char *line)
{
	char **tokens;

	tokens = ft_strsplit(line, ' ');
	return (tokens);
}

void	exec_process(t_list *env, char **tokens)
{
	(void)env;
	pid_t	pid;
	char *path[2];

	path[0] = "PATH";
	path[1] = "/usr/bin";
	pid = fork();
	execve(tokens[0], tokens, path);
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
		//exec_process(env, tokens);
		helper(shell, line, tokens);
		free_tokens(tokens);
		free(line);
	}
	free(line);
}
