//
//  ft_number_length.c
//  PrintF
//
//  Created by Boisset on 22/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

#include "libft.h"

uint64_t   ft_number_length(uint64_t nb)
{
    unsigned long long  length;
    
    length = 0;
    if (nb == 0)
        return (1);
    else if (nb < 0)
    {
        nb *= -1;
        length++;
    }
    while (nb > 0)
    {
        nb /= 10;
        length++;
    }
    return (length);
}
