//
//  zero.c
//  PrintF
//
//  Created by Boisset on 15/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

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

char *minus_format(char *str, va_list args)
{
    return NULL;
}
