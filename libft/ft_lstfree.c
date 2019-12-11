//
//  ft_lstnew.c
//  PrintF
//
//  Created by Boisset on 22/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

#include "libft.h"

void ft_lstfree(t_list **a_list)
{
    t_list *list;
    t_list *temp;
    
    list = *a_list;
    while (list != NULL)
    {
        temp = list;
        list = temp->next;
        free(temp->content);
        free(temp);
    }
}

