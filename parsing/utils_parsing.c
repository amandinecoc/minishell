/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amandine <amandine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/02 21:41:04 by amandine          #+#    #+#             */
/*   Updated: 2026/04/02 21:43:04 by amandine         ###   ########.fr       */
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
