//
//  dot_star.c
//  PrintF
//
//  Created by Boisset on 15/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

#include "printf.h"

int is_dot_applicable(char c)
{
    return (( c == 's' || c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X') ? 1 : 0);
}

int     dot_pattern(char *str, int pos, t_flags_state *to_do, va_list arg)
{
    int i;
    int temp;
    
    i = pos + 1;
    if (str[i] == '*')
    {
        temp = va_arg(arg, int);
        temp = (temp < 0) ? temp * -1 : temp;
        to_do->dot_star = temp;
        return (i + 1);
    }
    to_do->dot_star = ft_edit_atoi(str, i - 1);
    while(ft_isdigit(str[i]) && str[i] != '\0')
        i++;
    return (i);
}

char    *dot_format(int count, char *str, char *prefix, t_flags_state *to_do)//count is to do->dot_star | str is current arg | prefix is an already fill string | type is the end char | args is list of ...
{
    int i;
    int str_len;
    
    i = 0;
    str = (prefix != NULL) ? prefix : str;
    str_len = ft_strlen(str);
    count = (ft_atoi(str) < 1 && to_do->type != 's' && to_do->type != 'x' && to_do->type != 'X' && str_len < count) ? count + 1 : count;
    count = (to_do->type != 's' && to_do->type != 'x' && to_do->type != 'X' && ft_strncmp(str, "0", str_len) == 0) ? count - 1: count;
    count = (count == -1 && to_do->type == 's') ? 0 : count;
    
    if ((to_do->type == 's' && str_len <= count) || (to_do->type != 's' && str_len >= count && str[0] != '0'))
        return (ft_strdup(str));
    else if (count < 1 && ((str[0] == '0' && to_do->type != 's') || (to_do->type == 's')))
        return (ft_substr(str, 1, count));
    else if (count < str_len)
        return (ft_substr(str, 0, count));
    return (add_char(count, str, NULL, 0, '0'));
}
