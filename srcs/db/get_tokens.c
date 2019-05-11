/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 09:46:42 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/11 17:34:06 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

void	tilde_converter(t_core *shell, char **tokens)
{
	t_list	*env;
	char	*path;
	size_t	i;

	i = 0;
	path = NULL;
	env = shell->env;
	while (tokens[i])
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
		i++;
	}
}

void	exp_var_converter(t_core *shell, char **tokens)
{
	t_list	*var;
	char	*tmp;
	size_t	i;

	i = 1;
	tmp = NULL;
	while (tokens[i])
	{
		if (tokens[i][0] == '$')
		{
			tmp = ft_strsub(tokens[i], 1, ft_strlen(tokens[i]));
			var = shell->var;
			while (var)
			{
				if (ft_strequ(((t_db*)(var->content))->symbol, tmp) == TRUE)
				{
					ft_strdel(&tokens[i]);
					tokens[i] = ft_strdup(((t_db*)(var->content))->value);
					ft_strdel(&tmp);
				}
				var = var->next;
			}
		}
		i++;
	}
}

int8_t	get_tokens(t_core *shell, char *line, char ***tokens)
{
	*tokens = ft_strsplit(line, " \t");
	if (**tokens == NULL)
		return (FAILURE);
	exp_var_converter(shell, *tokens);
	tilde_converter(shell, *tokens);
	return (SUCCESS);
}
