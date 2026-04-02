/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandine <amandine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 21:05:01 by amandine          #+#    #+#             */
/*   Updated: 2026/04/02 21:44:12 by amandine         ###   ########.fr       */
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

/* ************************************************************************** */
/*CHECK_LINE*/
int check_line(char *line);
int check_quote(char *line, int i, int pos);
int check_wrong_char(char *line, int i, int pos);

/* ************************************************************************** */
/*UTILS_PARSING*/
int goto_char(char to_find, char *str, int pos);

/* ************************************************************************** */
/*PARSING*/
int parsing_minishell(char *line);

#endif