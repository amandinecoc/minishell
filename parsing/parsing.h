/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandine <amandine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 21:05:01 by amandine          #+#    #+#             */
/*   Updated: 2026/04/03 21:10:18 by amandine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

/* ************************************************************************** */
/*INCLUDES*/

/* ************************************************************************** */
/*TYPEDEF*/
typedef enum e_status
{
	Success,
	Malloc_failure,
	Error_wrong_char,
	Error_open_quote,
	Error,
	Empty,
}			t_status;

typedef struct s_parsing
{
	char	*start_line;
	char	*parser_line;
	char	**cut_line;
	int		len_tab;
}			t_parsing;

typedef enum e_type
{
	Pipe,
	Commande,
	Option_commande,
	Input,
	Output,
	Redirection,
}			t_type;

/* ************************************************************************** */
/*CHECK_LINE*/
int			check_line(char *line);
int			check_quote(char *line, int i, int pos);
int			check_wrong_char(char *line, int i, int pos);

/* ************************************************************************** */
/*UTILS_PARSING*/
int			goto_char(char to_find, char *str, int pos);

/* ************************************************************************** */
/*PARSING*/
int			parsing_minishell(char *line, char **envp);
int			fill_struct_parsing(char *line, t_parsing *data_parsing);

#endif