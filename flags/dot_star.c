//
//  dot_star.c
//  PrintF
//
//  Created by Boisset on 15/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

#include "printf.h"

int dot_star_pattern(char *str)
{
    return ((str[2] == '*') ? 0 : 2);
}

char *dot_star_format(char *str, va_list args)
{
    return NULL;
}
