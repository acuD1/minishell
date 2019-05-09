/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/05 10:16:16 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/09 16:59:07 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <limits.h>

char		**tokens_parser(t_core *shell, char *line)
{
	t_list	*env;
	char	**tokens;
	char	*path;
	size_t	i;

	i = 0;
	env = shell->env;
	tokens = ft_strsplit(line, ' ');
	path = NULL;
	while (tokens[++i])
	{
		if (ft_strequ(tokens[0], "~") == FALSE && tokens[i][0] == '~')
		{
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
	}
	return (tokens);
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
		tokens = tokens_parser(shell, line);
		if ((exec_builtins(shell, tokens)) == SUCCESS)
		{
			free_prompt(shell, tokens, line);
			if (shell->exit == TRUE)
				return ;
			continue ;
		}
		exec_process(shell, tokens);
		logger(shell, line, tokens);
		free_prompt(shell, tokens, line);
	}
	ft_strdel(&line);
}
