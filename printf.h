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

typedef struct              s_list
{
    void                    *content;
    struct s_flags_state    *to_do;
    struct s_list           *next;
}                           t_list;

typedef struct      s_flags_state
{
    int             zero_left;
    int             space_left;
    int             space_right;
    int             first_digit_to_zero;
    int             dot_star;
    char            type;
}                   t_flags_state;

/* misc.c */
void    ft_putstr(const char *str);
t_list  *ft_lstnew(void *content);
void    ft_lstadd_back(t_list **alst, t_list *new);
char    *ft_substr(char const *s, size_t start, size_t len);
int     ft_isdigit(int c);
int     ft_edit_atoi(const char *str);
int     ft_number_length(int nb);
int     ft_strlen(const char *s);
char    *ft_itoa(int n);
char        *ft_strdup(const char *s1)
t_flags_state *init_to_do(void);

/* main.c */
int     is_end_of_arg(char c);
int     get_type_by_letter(char c);

/* flags/zero.c */
int zero_pattern(char *str, int pos, t_flags_state *to_do);
char *zero_format(char *str, va_list args);

/* flags/minus.c */
int minus_pattern(char *str, int pos, t_flags_state *to_do);
char *minus_format(char *str, va_list args);

/* flags/dot-star.c */
int dot_star_pattern(char *str, int pos, t_flags_state *to_do);
char *dot_star_format(char *str, va_list args);

/* flags/zero.c */
int digit_pattern(char *str, int pos, t_flags_state *to_do);

#endif /* misc_h */
