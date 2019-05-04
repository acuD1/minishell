/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/11 13:36:24 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/04 17:07:01 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**token_parser(char *line)
{
	char	**tokens;

	tokens = ft_strsplit(line, ' ');
	return (tokens);
}

char	*find_file(char **path, char *filename)
{
	DIR				*content;
	struct dirent	*dir;
	int				i;

	i = 0;
	while (path[i])
	{
		if (!(content = opendir(path[i])))
		{
			ft_mprintf(STDERR_FILENO, "%sFailed opendir(%s) ! Continuing...\n%s", C_R, path[i], C_X);
			continue;
		}
		if (content)
		{
			while ((dir = readdir(content)))
			{
				if (ft_strequ(filename, dir->d_name))
				{
					closedir(content);
					return (ft_strdup(path[i]));
				}
				continue;
			}
		}
		closedir(content);
		i++;
	}
	return (NULL);
}

void		get_path(t_core *shell, char *filename)
{
	t_list	*env;
	char	**path;
	char	*tmp;

	env = shell->env;
	if (!filename)
		return ;
	if (filename[0] == '.' || filename[0] == '/')
	{
		shell->bin_path = ft_strdup(filename);
		return ;
	}
	tmp = ft_strjoin("/", filename);
	while (env)
	{
		if (ft_strequ(ENV_DB->symbol, "PATH"))
		{
			path = ft_strsplit(ENV_DB->value, ':');
			shell->bin_path = ft_strjoin_free(find_file(path, filename), tmp, 3);
			free_2dtab(path);
			return ;
		}
		env = env->next;
	}
}

char		**env_to_envp(t_core *shell)
{
	t_list	*env;
	char	**envp;
	int		i;

	i = 0;
	env = shell->env;
	if (!(envp = ft_memalloc(sizeof(envp) * ((ft_lstlen(env)) + 1))))
		return (NULL);
	while (env)
	{
		envp[i] = ft_strjoin_free(ft_strjoin(ENV_DB->symbol, "="), ENV_DB->value, 1);
		env = env->next;
		i++;
	}
	envp[i] = NULL;
	return (envp);
}

int		exec_handler(t_core *shell, char **tokens, char **envp)
{
	if (shell->bin_path == NULL)
	{
			ft_mprintf(STDERR_FILENO, "minishell: command not found: %s\n", tokens[0]);
		return (0);
	}
	if (access(shell->bin_path, X_OK) == -1)
	{
		ft_mprintf(STDERR_FILENO, "minishell: permission denied: %s\n", tokens[0]);
		return (0);
	}
	if (execve(shell->bin_path, tokens, envp) < 0)
	{
		ft_mprintf(STDERR_FILENO, "%sExecve failed ! PATH may be incorrect\n%s",
			C_R, C_X);
		return (0);
	}
	return (1);
}

int		exec_builtins(t_core *shell, char **tokens)
{
	//Tableau de pointeur sur fonctions ICI
	if (ft_strequ(tokens[0], "exit"))
	{
		shell->exit = 1;
		return (0);
	}
	return (1);
}

int		exec_process(t_core *shell, char **tokens)
{
	char	**envp;
	int		status;

	if (tokens[0] == NULL || !(exec_builtins(shell, tokens)))
		return (0);
	get_path(shell, tokens[0]);
	envp = env_to_envp(shell);
	if ((shell->child_pid = fork()) < 0)
	{
		ft_mprintf(STDERR_FILENO, "%sFork failed !\n%s",
			C_R, C_X);
		exit(1);
	}
	if (shell->child_pid == 0)
	{
		if (!(exec_handler(shell, tokens, envp)))
			exit(1);
	}
	else
		waitpid(shell->child_pid, &status, WUNTRACED);
	free(shell->bin_path);
	free_2dtab(envp);
	return (1);
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
		if (!(exec_process(shell, tokens)))
		{
			free_2dtab(tokens);
			free(line);
			return ;
		}
		// LOGGER
		helper(shell, line, tokens);
		// LOGGER
		free_2dtab(tokens);
		free(line);
	}
	free(line);
}
