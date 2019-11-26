//
//  misc.c
//  PrintF
//
//  Created by Boisset on 13/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

#include "printf.h"

t_flags_state *init_to_do(void)
{
    t_flags_state *new;
    
    if (!(new = (t_flags_state*)malloc(sizeof(t_flags_state))))
        return (NULL);
    new->zero_left = 0;
    new->space_left = 0;
    new->space_right = 0;
    new->zero_left = 0;
    new->first_digit_to_zero = 0;
    new->dot_star = 0;
    new->percentage = 0;
    new->type = '0';
    return (new);
}

int             ft_edit_atoi(const char *str)
{
    int i;
    int number;
    
    i = 0;
    number = 0;
    if (str[0] == '\0')
        return (0);
    while (!ft_isdigit(str[i]))
    {
        i++;
        if (str[i] == '\0')
            return (-1);
    }
    while (ft_isdigit(str[i]) && str[i] != '\0')
        number = number * 10 + (str[i++] - '0');
    return (number);
}

char *num_to_hex(uint64_t num)
{
    char *res;
    uint64_t i;
    uint64_t temp;
    
    i = 0;
    if (!(res = malloc(sizeof(char) * ft_number_length(num))))
        return (NULL);
    while (num != 0)
    {
        temp = num % 16;
        if (temp < 10)
            res[i++] = temp + 48;
        else
            res[i++] = temp + 55;
        num /= 16;
    }
    res[i] = '\0';
    ft_strrev(res);
    return (res);
}
