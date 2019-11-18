//
//  misc.h
//  PrintF
//
//  Created by Boisset on 13/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

#ifndef misc_h
#define misc_h

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

typedef struct      s_list
{
    void            *content;
    struct s_list   *next;
}                   t_list;

typedef struct      s_flags_state
{
    int             minus;
    int             zero;
    int             dot_star;
    int             hastag;
}                   t_flags_state;

void    ft_putstr(const char *str);
t_list  *ft_lstnew(void *content);
void    ft_lstadd_back(t_list **alst, t_list *new);
char    *ft_substr(char const *s, size_t start, size_t len);
int     ft_isdigit(int c);
int     ft_edit_atoi(const char *str);
int     ft_number_length(int nb);
int    ft_strlen(const char *s);
char        *ft_itoa(int n)

int     is_end_of_arg(char c);
int     get_type_by_letter(char c);

int zero_pattern(char *str);
char *zero_format(char *str, va_list args);

int minus_pattern(char *str);
char *minus_format(char *str, va_list args);

int dot_star_pattern(char *str);
char *dot_star_format(char *str, va_list args);

#endif /* misc_h */
