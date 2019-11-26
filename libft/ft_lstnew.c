//
//  ft_lstnew.c
//  PrintF
//
//  Created by Boisset on 22/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

#include "libft.h"

t_list  *ft_lstnew(void *content)
{
    t_list *new;
    
    if (!(new = (t_list*)malloc(sizeof(t_list))))
        return (NULL);
    if (!content)
        new->content = NULL;
    else
        new->content = content;
    new->next = NULL;
    return (new);
}
