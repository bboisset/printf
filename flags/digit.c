//
//  digit.c
//  PrintF
//
//  Created by Boisset on 15/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

#include "printf.h"
#include <stdarg.h>

int digit_pattern(char *str, int pos, t_flags_state *to_do, va_list arg)
{
    int i;
    int temp;
    
    i = pos;
    if (str[i] == '*')
    {
        temp = va_arg(arg, int);
        if (temp > 0)
            to_do->space_left = temp;
        else
            to_do->space_right = temp * -1;
        return (i + 1);
    }
    to_do->space_left = ft_edit_atoi(str, i);//may bug on value as z after "."
    while(ft_isdigit(str[i]) && str[i] != '\0')
        i++;
    return (i);
}

static char *minus_edition(char *str, int *negative, int type)
{
    if(type == 0)
    {
        *negative = 1;
        return (++str);//leak ?
    }
    else
        return (ft_strjoin("-",str));//leak ?
}

char *add_char(int space_to_add, char *str, char *prefix, int orientation, char charset)
{
    char *temp;
    char *new_str;
    int str_len;
    int i;
    int negative;
    
    i = 0;
    negative = 0;
    str = (prefix != NULL) ? prefix : str;
    if (charset == '0' && str[0] == '-')
    {
        str = minus_edition(str, &negative, 0);
        space_to_add--;
    }
    str_len = ft_strlen(str);
    space_to_add = (space_to_add - str_len > 0) ? space_to_add - str_len : 0;
    if (!(temp = malloc((space_to_add + 1) * sizeof(char))))
        return (NULL);
    while (space_to_add > 0)
    {
        temp[i++] = charset;
        space_to_add--;
    }
    temp[i] = '\0';
    if (orientation == 0)
        new_str = ft_strjoin(temp, str);
    else
        new_str = ft_strjoin(str, temp);
    free(temp);
    if (negative)
        new_str = minus_edition(new_str, &negative, 1);
    return (new_str);
}
