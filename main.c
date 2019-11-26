//
//  main.c
//  PrintF
//
//  Created by Boisset on 13/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

#include "printf.h"

int is_end_of_arg(char c)
{
    return ((c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == '%') ? 1 : 0);
}

char *get_arguments_pointer(char type, va_list args)
{
    char *res;
    uintmax_t temp;
    
    if (type == 'p')
        temp = va_arg(args, uintmax_t);
    else
        temp = va_arg(args, unsigned int);
    res = num_to_hex(temp);
    if (type == 'X')
        return (res);
    res = ft_strlowcase(res);
    if (type == 'x')
        return (res);
    else if (type == 'p')
        return (ft_strjoin("0x", res));
    return (NULL);
}

char *get_arguments(char type, va_list args, int dot_star)
{
    char *res;
    
    res = NULL;
    if (type == 'u' || dot_star == -1)
        res = ft_itoa(va_arg(args, unsigned int));
    else if (type == 'c')
        res = ft_char_to_string(va_arg(args, uintmax_t));
    else if (type == 's')
        res = va_arg(args, char*);
    else if (type == 'p' || type == 'x' || type == 'X')
        res = get_arguments_pointer(type, args);
    else if (type == 'i' || type == 'd')
        res = ft_itoa((va_arg(args, int)));
    else if (type == '%')
        res = ft_char_to_string('%');
    return (res);
}

char *convert_string(va_list args, int *args_idx, t_flags_state **to_do)
{
    char *new_str;
    char *current_arg;
    t_flags_state *temp;
    
    temp = *to_do;
    new_str = NULL;
    if (!(current_arg = get_arguments(temp->type, args, temp->dot_star)))
        return (NULL);
    if (temp->zero_left)
        new_str = add_char(temp->zero_left, current_arg, 0, '0');
    else if (temp->space_left)
        new_str = add_char(temp->space_left, current_arg, 0, ' ');
    else if (temp->space_right)
        new_str = add_char(temp->space_right, current_arg, 1, ' ');
    else if (temp->first_digit_to_zero)
        new_str = NULL;
    else if (temp->dot_star)
        new_str = dot_format(temp->dot_star, current_arg, temp->type, args);
    else
        new_str = ft_strdup(current_arg);
    //free(current_arg);
    return (new_str);
}

void print_list(t_list *list)
{
    while (list != NULL)
    {
        ft_putstr(list->content);
        list = list->next;
    }
}

int assign_type(char c, t_flags_state *to_do)
{
    if (is_end_of_arg(c))
    {
        to_do->type = c;
        return (0);
    }
    return (-1);
}

/* Should Return something like %-10x | %#-10x | %d | %#-10-50x...
 */
int is_valid_pattern(char *str, t_flags_state **to_do)
{
    int i;
    
    i = 1;
    *to_do = init_to_do();
    while (str[i] != '\0')
    {
        if (str[i] == '0')
            i = zero_pattern(str, i, *to_do);
        else if (ft_isdigit(str[i]))
            i = digit_pattern(str, i, *to_do);
        else if (str[i] == '-')
            i = minus_pattern(str, i, *to_do);
        else if (str[i] == '.')
            i = dot_pattern(str, i, *to_do);
        i++;
    }
    return (assign_type(str[i - 1], *to_do));
}

int parse_string(const char *str, t_list **list, va_list args, int *args_idx)
{
    int i;
    int j;
    int last_addition;
    t_flags_state *to_do;
    char *pattern;
    
    i = 0;
    j = 0;
    last_addition = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '%')
        {
            ft_lstadd_back(list, ft_lstnew(ft_substr(str, last_addition, i - last_addition)));
            while ((!is_end_of_arg(str[i + j]) || (str[i + j] == '%' && j == 0)) && str[i + j] != '\0')
                j++;
            if (is_valid_pattern(pattern = ft_substr(str, i, j + 1), &to_do) == 0)
            {
                ft_lstadd_back(list, ft_lstnew(convert_string(args, args_idx, &to_do)));
                j += 1;
            }
            i += j;
            last_addition = i;
            j = 0;
            free(pattern);
        }
        i++;
    }
    ft_lstadd_back(list, ft_lstnew(ft_substr(str, last_addition, i - last_addition)));
    return (1);
}

int ft_printf(const char *format, ...)
{
    t_list  *list;
    va_list args;
    int     args_idx;
    
    va_start(args, format);
    list = NULL;
    args_idx = 0;
    parse_string(format, &list, args, &args_idx);
    va_end(args);
    print_list(list);
    //free list
    return (0);
}

int main(void) {
    printf( "%i\n", 123);
    ft_printf( "%i\n", 123);
    return 0;
}
