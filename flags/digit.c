//
//  zero.c
//  PrintF
//
//  Created by Boisset on 15/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

#include "printf.h"
#include <stdarg.h>

int digit_pattern(char *str, int pos, t_flags_state *to_do)
{
    int i;
    
    i = pos;
    to_do->space_left = ft_edit_atoi(str);
    while(ft_isdigit(str[i]) && str[i] != '\0')
        i++;
    return (i);
}

char *add_char(int space_to_add, char *str, int orientation, char charset)
{
    char *temp;
    char *new_str;
    int str_len;
    int i;
    
    i = 0;
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
    return (new_str);
}
