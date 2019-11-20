//
//  minus.c
//  PrintF
//
//  Created by Boisset on 15/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

#include "printf.h"

int minus_pattern(char *str, int pos, t_flags_state *to_do)
{
    int i;
    
    i = pos + 1;
    to_do->space_right = ft_edit_atoi(str);
    while(ft_isdigit(str[i]))
        i++;
    return (i);
}

char *minus_format(char *str, va_list args)
{
    return NULL;
}
