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
#include "libft.h"

typedef struct      s_flags_state
{
    int             zero_left;
    int             space_left;
    int             space_right;
    int             first_digit_to_zero;
    int             dot_star;
    int             percentage;
    char            type;
}                   t_flags_state;

/* misc.c */
int                 ft_edit_atoi(const char *str);
t_flags_state       *init_to_do(void);
char                *num_to_hex(uint64_t num);

/* main.c */
int                 is_end_of_arg(char c);
int                 get_type_by_letter(char c);
char                *get_arguments(char type, va_list args, int dot_star);

/* flags/zero.c */
int                 zero_pattern(char *str, int pos, t_flags_state *to_do);
char                *zero_format(char *str, va_list args);

/* flags/minus.c */
int                 minus_pattern(char *str, int pos, t_flags_state *to_do);
char                *minus_format(char *str, va_list args);

/* flags/dot-star.c */
int                 dot_pattern(char *str, int pos, t_flags_state *to_do);
char                *dot_format(int count, char *str, char type, va_list args);

/* flags/zero.c */
int                 digit_pattern(char *str, int pos, t_flags_state *to_do);
char                *add_char(int space_to_add, char *str, int orientation, char charset);

#endif /* misc_h */
