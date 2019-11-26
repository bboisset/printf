//
//  ft_putstr.c
//  PrintF
//
//  Created by Boisset on 22/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

#include "libft.h"

void    ft_putstr(const char *str)
{
    int i;
    
    i = 0;
    if (str)
        while(str[i] != '\0')
            write(1, &str[i++], 1);
}
