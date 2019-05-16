/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_builtin_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 11:01:12 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/16 11:04:50 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "unistd.h"

void	env_builtin_usage(char **tokens)
{
	ft_mprintf(STDERR_FILENO, "env: illegal option -- %c\n", tokens[1][1]);
	ft_putendl_fd("usage: env [-i] [name=value ...] [utility [argument ...]]",
		STDERR_FILENO);
}

uint8_t	tokens_parser_checker(char *tokens)
{
	if (ft_strequ(tokens, "env") == TRUE
		|| ft_strequ(tokens, "-i") == TRUE
		|| ft_strchr(tokens, '=') != NULL)
		return (TRUE);
	else
		return (FALSE);
}

void	env_builtin_printer(t_core *shell, char **tokens)
{
	t_list	*tmp_env;
	size_t	i;

	i = 0;
	tmp_env = shell->tmp_env;
	if (ft_strequ(tokens[1], "-i") == FALSE)
	{
		if (tokens[1] == NULL)
			tmp_env = shell->env;
		while (tmp_env)
		{
			ft_mprintf(STDOUT_FILENO, "%s=%s\n",
				((t_db*)(tmp_env->content))->symbol,
				((t_db*)(tmp_env->content))->value);
			tmp_env = tmp_env->next;
		}
		return ;
	}
	while (tokens && tokens[i])
	{
		if (ft_strchr(tokens[i], '=') != NULL)
			ft_mprintf(STDOUT_FILENO, "%s\n", tokens[i]);
		i++;
	}
}
