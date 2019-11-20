//
//  dot_star.c
//  PrintF
//
//  Created by Boisset on 15/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

#include "printf.h"

int dot_star_pattern(char *str, int pos, t_flags_state *to_do)
{
    int i;
    
    i = pos + 1;
    if (str[i] == '*')
    {
        to_do->dot_star = 1;
        return (pos);
    }
    return (pos - 1);
}

char *dot_star_format(char *str, va_list args)
{
    return NULL;
}
