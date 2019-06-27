/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_builtin_handler.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/01 11:47:14 by arsciand          #+#    #+#             */
/*   Updated: 2019/06/27 13:40:07 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>

void	cd_handler(char *tokens, uint8_t handler)
{
	if (handler & CD_ARG_ERROR)
		ft_mprintf(STDERR_FILENO, "minishell: cd: Too many arguments\n");
	if (handler & CD_DIR_ERROR)
		ft_mprintf(STDERR_FILENO,
			"minishell: cd: %s: No such file or directory\n", tokens);
	if (handler & CD_PERM_ERROR)
		ft_mprintf(STDERR_FILENO, "minishell: cd: %s: Permission denied\n",
			tokens);
	if (handler & CD_USAGE)
		ft_mprintf(STDERR_FILENO,
			"minishell: cd: %s: invalid option\ncd: usage: cd [dir]\n",
			tokens);
	if (handler & CD_OLDPWD_NULL)
		ft_mprintf(STDERR_FILENO, "minishell: cd: OLDPWD not set\n");
	if (handler & CD_HOME_NULL)
		ft_mprintf(STDERR_FILENO, "minishell: cd: HOME not set\n");
}
