//
//  ft_strrev.c
//  PrintF
//
//  Created by Boisset on 22/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

#include "libft.h"

char    *ft_strrev(char *src)
{
    int        length;
    int        i;
    char    temp;
    
    length = ft_strlen(src);
    i = -1;
    while (++i < length / 2)
    {
        temp = src[i];
        src[i] = src[length - i - 1];
        src[length - i - 1] = temp;
    }
    return (src);
}
