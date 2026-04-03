/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandine <amandine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 18:10:56 by amandine          #+#    #+#             */
/*   Updated: 2026/04/03 21:14:03 by amandine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* ************************************************************************** */
/*INCLUDES*/
# include "bultin/bultin.h"
# include "exec/exec.h"
# include "libft/libft.h"
# include "parsing/parsing.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

/* ************************************************************************** */
/*TYPEDEF*/

typedef struct s_minishell
{
	char	**envp;
}			t_minishell;

/* ************************************************************************** */
/*MINISHELL*/
int			fill_struct_minishell(t_minishell *ms_data, char **envp);

#endif