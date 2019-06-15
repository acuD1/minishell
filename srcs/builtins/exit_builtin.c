/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 11:00:33 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/15 15:53:13 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	exit_builtin(t_core *shell, char **tokens)
{
	size_t	i;

	i = 0;
	if (ft_tablen(tokens) > 2)
	{
		ft_mprintf(STDERR_FILENO,
			"exit\nminishell: exit: too many arguments\n");
		return ;
	}
	shell->exit = TRUE;
	while (tokens[1] && tokens[1][i])
	{
		if (ft_isdigit(tokens[1][i]) == FALSE)
		{
			ft_mprintf(STDERR_FILENO,
				"exit\nminishell: exit: numeric argument required\n");
			return ;
		}
		i++;
	}
	if (tokens[1] != NULL)
		shell->exit_value = ft_atoi(tokens[1]);
}
