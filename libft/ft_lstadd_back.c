//
//  ft_lstadd_back.c
//  PrintF
//
//  Created by Boisset on 22/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

#include "libft.h"

void    ft_lstadd_back(t_list **alst, t_list *new)
{
    t_list *temp;
    
    if (new)
    {
        if (*alst)
        {
            temp = *alst;
            while (temp->next)
                temp = temp->next;
            temp->next = new;
        }
        else
            *alst = new;
    }
}
