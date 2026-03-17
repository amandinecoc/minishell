/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandine <amandine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/14 12:43:56 by amandine          #+#    #+#             */
/*   Updated: 2026/03/17 16:09:37 by amandine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int goto_char(char to_find, char *str, int pos)
{
    while (str[pos] != '\0')
    {
        if (str[pos] == to_find)
            return (pos);
        pos++;
    }
    return (pos);
}

int parsing_minishell(char *line)
{
    int i;
    int pos;
    
    i = 0;
    if (line = NULL)
        return (NULL);
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
