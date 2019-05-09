/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/06 12:41:39 by arsciand          #+#    #+#             */
/*   Updated: 2019/05/09 15:47:12 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include "define.h"
# include "struct.h"

# include <stdio.h>

/*
**	Core
*/

void				signal_handler(void);
void				exec_prompt(t_core *shell);
void				exec_process(t_core *shell, char **tokens);
int8_t				exec_builtins(t_core *shell, char **tokens);
int8_t				exit_handler(t_core *shell, int status);
void				free_tab(char **tokens);
void				free_list(t_list *env);
void				free_prompt(t_core *shell, char **tokens, char *line);
void				free_core(t_core *shell);

/*
** DB
*/

void				init_shell(t_core *shell);
int8_t				set_env(t_core *shell, char **environ);
int8_t				get_opt(int ac, char **av, t_core *shell);
char				**get_envp(t_core *shell);
char				*get_bin(t_core *shell, const char *filename);

/*
**	Misc
*/

void				logger(t_core *shell, char *line, char **tokens);
void				open_logger_fd(t_core *shell, char *av);
void				credit(t_core *shell);
void				init_prompt(void);
void				print_opt(t_core *shell);

#endif
