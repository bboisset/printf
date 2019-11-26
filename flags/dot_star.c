//
//  dot_star.c
//  PrintF
//
//  Created by Boisset on 15/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

#include "printf.h"

int     dot_pattern(char *str, int pos, t_flags_state *to_do)
{
    int i;
    
    i = pos + 1;
    to_do->dot_star = ft_edit_atoi(str);
    if (to_do->dot_star == -1 && str[i] != '*')
        to_do->dot_star = -2;
    while(ft_isdigit(str[i]) && str[i] != '\0')
        i++;
    return (i);
}

char    *dot_format(int count, char *str, char type, va_list args)
{
    int i;
    int str_len;
    
    i = 0;
    str_len = ft_strlen(str);
    if (count == -1)
    {
        count = ft_atoi(str);
        str = get_arguments(type, args, 0);
        str_len = ft_strlen(str);
        if (count < str_len)
            return (ft_substr(str, 0, count));
        return (add_char(count, str, 0, '0'));
    }
    else if (type == 's' && count >= str_len)
        return (ft_strdup(str));
    else if (count < str_len)
       return (ft_substr(str, 0, count));
    return (add_char(count, str, 0, '0'));
}
