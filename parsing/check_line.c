/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandine <amandine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:43:56 by amandine          #+#    #+#             */
/*   Updated: 2026/04/02 21:43:33 by amandine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int check_quote(char *line, int i, int pos)
{
    while (line[i] != '\0')
    {
        pos = i;
        if (line[i] == '"' || line[i] == 39)
        {
            i = goto_char(line[pos], line, pos);
            if (line[i] == '\0')
                return (Error_open_quote);
        }
        i++;
    }
    return (Success);
}

int check_wrong_char(char *line, int i, int pos)
{
    while (line[i] != '\0')
    {
        if (line[i] == 59 || line[i] == 92)
            return (Error_wrong_char);
        if (line[i] == '"' || line[i] == 39)
            i = goto_char(line[pos], line, pos);
        i++;
    }
    return (Success);
}

int check_line(char *line)
{
    int i;
    int pos;
    int status;
    
    i = 0;
    pos = 0;
    status = check_quote(line, i, pos);
    if (status != Success)
        return (status);
    status = check_wrong_char(line, i, pos);
    if (status != Success)
        return (status);
    return (Success);
}
