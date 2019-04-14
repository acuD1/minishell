/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:43:49 by arsciand          #+#    #+#             */
/*   Updated: 2019/04/14 13:48:24 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <signal.h>

char	**token_parser(char *line)
{
	char **tokens;

	tokens = ft_strsplit(line, ' ');
	return (tokens);
}

void	token_helper(char **tokens, t_opt *opt)
{
	int fd;
	int	i;

	i = 0;
	if (!(fd = open_logger(opt)))
		return ;
	while (tokens[i])
	{
		ft_mprintf(fd, "token[%d] = |%s|\n", i, tokens[i]);
		i++;
	}
}

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		free(tokens[i]);
		i++;
	}
	free(tokens);
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

void	exec_prompt(t_list *env, t_opt *opt, t_build *build)
{
	char	**tokens;
	char	*line;
	int		status;

	status = 1;
	credit(build);
	while (status)
	{
		init_prompt();
		if (!(status = get_next_line(STDIN_FILENO, &line)))
			break ;
		tokens = token_parser(line);
		exec_process(env, tokens);
		helper(env, opt, build, line);
		token_helper(tokens, opt);
		free_tokens(tokens);
		free(line);
	}
	free(line);
}

int		main(int ac, char **av, char **environ)
{
	t_build build;
	t_opt	opt;
	t_list	*env;
	char *line = NULL; //For logging

	init_build(&build);
	ft_bzero(&opt, sizeof(t_opt));
	if (!(get_opt(ac, av, &opt)))
		return (exit_status(&opt, __func__, __FILE__, __LINE__));
	if (!(env = set_env(environ)))
	{
		opt.fail = 1;
		helper(env, &opt, &build, line);
		return (exit_status(&opt, __func__, __FILE__, __LINE__));
	}
	helper(env, &opt, &build, line);
	signal_handler();
	if (!opt.v && !opt.h)
		exec_prompt(env, &opt, &build);
	free_list(env);
	return (exit_status(&opt, __func__, __FILE__, __LINE__));
}
