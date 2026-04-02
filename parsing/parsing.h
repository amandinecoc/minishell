/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandine <amandine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 21:05:01 by amandine          #+#    #+#             */
/*   Updated: 2026/04/02 21:36:48 by amandine         ###   ########.fr       */
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
	Error_wrong_char,
	Error_open_quote,
	Error,
	Empty,
}			t_status;

// typedef struct s_pipex
// {
// 	char	*file1;
// 	char	*cmd1;
// 	char	*file2;
// 	char	*cmd2;
// 	char	**tab_cmd1;
// 	char	**tab_cmd2;
// 	char	**tab_path;
// }			t_pipex;

/* ************************************************************************** */
/*PARSING*/
int parsing_minishell(char *line);
int goto_char(char to_find, char *str, int pos);
int check_line(char *line);
int check_quote(char *line, int i, int pos);
int check_wrong_char(char *line, int i, int pos);

/* ************************************************************************** */
/*PARSING_*/

#endif