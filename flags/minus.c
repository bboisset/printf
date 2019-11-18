//
//  minus.c
//  PrintF
//
//  Created by Boisset on 15/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

#include "printf.h"

int minus_pattern(char *str)
{
    int i;
    
    i = 1;
    while (ft_isdigit(str[i]))
        i++;
    if (is_end_of_arg(str[i]))
        return (0);
    return (i);
}

char *minus_format(char *str, va_list args)
{
    return NULL;
}
