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

char *get_arguments(char type, va_list args, t_flags_state *to_do)
{
    char *res;
    char temp;
    
    res = NULL;
    if (type == 'u')
        res = ft_itoa_uint64_t(va_arg(args, uint64_t));
    else if (type == 'c')
    {
        temp = va_arg(args, uintmax_t);
        if (temp == '\0')
            to_do->addional_length += 1;
        res = ft_char_to_string(temp);
    }
    else if (type == 's')
        res = handle_ft_strdup(va_arg(args, char*));
    else if (type == 'p' || type == 'x' || type == 'X')
        res = get_arguments_pointer(type, args);
    else if (type == 'i' || type == 'd')
        res = ft_itoa((va_arg(args, int)));
    else if (type == '%')
        res = ft_char_to_string('%');
    if (res == NULL && type == 's')
        res = ft_strdup("(null)");
    else if(res == NULL && type == 'p')
        res = ft_strdup("0x0");
    else if (res == NULL)
        res = ft_char_to_string('0');
    return (res);
}

char *convert_string(va_list args, t_flags_state **to_do)
{
    char *new_str;
    char *current_arg;
    t_flags_state *temp;
    
    temp = *to_do;
    new_str = NULL;
    if (!(current_arg = get_arguments(temp->type, args, *to_do)))
        return (NULL);
    temp->space_left = (temp->type == 'c' && current_arg[0] == 0) ? temp->space_left - 1 : temp->space_left;
    temp->space_right = (temp->type == 'c' && current_arg[0] == '\0') ? temp->space_right - 1 : temp->space_right;
    temp->zero_left = (temp->type == 'c' && current_arg[0] == '\0') ? temp->zero_left - 1 : temp->zero_left;
    if (temp->dot_star != -2 && temp->type != '%' && temp->type != 'c' && temp->type != 'p')
        new_str = dot_format(temp->dot_star, current_arg, new_str, temp);
    if (temp->space_left)
        new_str = add_char(temp->space_left, current_arg, new_str, 0, ' ');
    if (temp->space_right)
        new_str = add_char(temp->space_right, current_arg, new_str, 1, ' ');
    if (temp->zero_left)
        new_str = add_char(temp->zero_left, current_arg, new_str, 0, ((temp->type != 's' && is_dot_applicable(temp->type) && temp->dot_star != -2)) ? ' ' : '0');
    if (temp->first_digit_to_zero)
        new_str = NULL;
    if (new_str == NULL)
        new_str = ft_strdup(current_arg);
    free(current_arg);
    return (new_str);
}

int print_list(t_list *list)
{
    int strlen;
    
    strlen = 0;
    while (list != NULL)
    {
        ft_putstr(list->content);
        strlen += ft_strlen(list->content);
        list = list->next;
    }
    return (strlen);
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
int is_valid_pattern(char *str, t_flags_state **to_do, va_list args)
{
    int i;
    
    i = 1;
    *to_do = init_to_do();
    while (str[i] != '\0')
    {
        if (str[i] == '0')
            i = zero_pattern(str, i, *to_do, args);
        else if (ft_isdigit(str[i]) || str[i] == '*')
            i = digit_pattern(str, i, *to_do, args);
        else if (str[i] == '.')
            i = dot_pattern(str, i, *to_do, args);
        else if (str[i] == '-')
            i = minus_pattern(str, i, *to_do, args);
        else
            i++;
    }
    return (assign_type(str[i - 1], *to_do));
}

int parse_string(const char *str, t_list **list, va_list args)
{
    int i;
    int j;
    int last_addition;
    int addional_length;
    t_flags_state *to_do;
    char *pattern;
    
    i = 0;
    j = 0;
    addional_length = 0;
    last_addition = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '%')
        {
            ft_lstadd_back(list, ft_lstnew(ft_substr(str, last_addition, i - last_addition)));
            while ((!is_end_of_arg(str[i + j]) || (str[i + j] == '%' && j == 0)) && str[i + j] != '\0')
                j++;
            if (is_valid_pattern(pattern = ft_substr(str, i, j + 1), &to_do, args) == 0)
            {
                ft_lstadd_back(list, ft_lstnew(convert_string(args, &to_do)));
                j += 1;
            }
            addional_length += to_do->addional_length;
            free(to_do);
            i += j;
            last_addition = i;
            j = 0;
            free(pattern);
        }
        else
            i++;
    }
    ft_lstadd_back(list, ft_lstnew(ft_substr(str, last_addition, i - last_addition)));
    return (addional_length);
}

int ft_printf(const char *format, ...)
{
    t_list  *list;
    va_list args;
    int strlen;
    int addional_length;
    
    addional_length = 0;
    va_start(args, format);
    list = NULL;
    addional_length = parse_string(format, &list, args);
    va_end(args);
    strlen = print_list(list) + addional_length;
    ft_lstfree(&list);
    return (strlen);
}
