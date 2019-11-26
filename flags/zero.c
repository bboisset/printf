/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:59:59 by bboisset          #+#    #+#             */
/*   Updated: 2019/11/26 15:00:03 by bboisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdarg.h>

int zero_pattern(char *str, int pos, t_flags_state *to_do)
{
    int i;
    
    i = pos + 1;
    to_do->zero_left = ft_edit_atoi(str);
    while(ft_isdigit(str[i]) && str[i] != '\0')
        i++;
    return (i);
}
