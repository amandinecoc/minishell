/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandine <amandine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:43:56 by amandine          #+#    #+#             */
/*   Updated: 2026/04/02 21:09:23 by amandine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int goto_char(char to_find, char *str, int pos)
{
    pos++;
    while (str[pos] != '\0')
    {
        if (str[pos] == to_find)
            return (pos);
        pos++;
    }
    return (pos);
}

int check_cote(char *line, int i, int pos)
{
    while (line[i] != '\0')
    {
        pos = i;
        if (line[i] == '"' || line[i] == 39)
        {
            i = goto_char(line[pos], line, pos);
            if (line[i] == '\0')
                return (EXIT_FAILURE); //faire enum error cote seule
        }
        i++;
    }
    return (EXIT_SUCCESS);
}

int check_false_char(char *line, int i, int pos)
{
    while (line[i] != '\0')
    {
        if (line[i] == 59 || line[i] == 92)
            return (EXIT_FAILURE);
        if (line[i] == '"' || line[i] == 39)
            i = goto_char(line[pos], line, pos);
        i++;
    }
    return (EXIT_SUCCESS);
}

int check_line(char *line)
{
    int i;
    int pos;
    int status;
    
    i = 0;
    pos = 0;
    status = check_cote(line, i, pos);
    if (status != EXIT_SUCCESS)
        return (status);
    status = check_false_char(line, i, pos);
    if (status != EXIT_SUCCESS)
        return (status);
    return (EXIT_SUCCESS);
}

int parsing_minishell(char *line)
{
    int status;
    
    status = check_line(line);
    if (status != EXIT_SUCCESS)
        return (status);
    return(EXIT_SUCCESS);
}
