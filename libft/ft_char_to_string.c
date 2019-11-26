//
//  ft_char_to_string.c
//  PrintF
//
//  Created by Boisset on 22/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

#include "libft.h"

char        *ft_char_to_string(char c)
{
    char *dest;
    
    if (!(dest = malloc(sizeof(char) * 2)))
        return (NULL);
    dest[0] = c;
    dest[1] = '\0';
    return (dest);
}
