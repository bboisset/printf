//
//  misc.c
//  PrintF
//
//  Created by Boisset on 13/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

#include "printf.h"

void    ft_putstr(const char *str)
{
    int i;
    
    i = 0;
    while(str[i] != '\0')
        write(1, &str[i++], 1);
}

int    ft_strlen(const char *s)
{
    int i;
    
    i = 0;
    while (s[i] != '\0')
        i++;
    return (i);
}

unsigned long long   ft_number_length(unsigned long long nb)
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


int    ft_isdigit(int c)
{
    return (c >= 48 && c <= 57) ? 1 : 0;
}

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
    new->type = '0';
    return (new);
}

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
    new->to_do = NULL;
    return (new);
}

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

char    *ft_substr(char const *s, size_t start, size_t len)
{
    char    *str2;
    size_t    i;
    size_t    s_len;
    
    s_len = (size_t)ft_strlen(s);
    start = (start > s_len ? s_len : start);
    len = (start + len > s_len) ? s_len - start : len;
    str2 = malloc((len + 1) * sizeof(char));
    if (!str2)
        return (NULL);
    i = 0;
    while (i < len && s[start + i] != '\0')
    {
        str2[i] = s[start + i];
        ++i;
    }
    str2[i] = '\0';
    return (str2);
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
        i++;
    while (ft_isdigit(str[i]) && str[i] != '\0')
        number = number * 10 + (str[i++] - '0');
    return (number);
}

static char    *ft_strcpy(char *dst, const char *src)
{
    size_t i;
    
    i = 0;
    while (src[i])
    {
        dst[i] = src[i];
        i++;
    }
    dst[i] = '\0';
    return (dst);
}

char        *ft_strdup(const char *s1)
{
    size_t    s1_len;
    char    *dest;
    
    s1_len = ft_strlen(s1);
    if (!(dest = (char *)malloc(sizeof(char) * s1_len + 1)))
        return (NULL);
    dest = ft_strcpy(dest, s1);
    return (dest);
}

char        *ft_char_to_string(char c)
{
    char *dest;
    
    if (!(dest = malloc(sizeof(char) * 2)))
        return (NULL);
    dest[0] = c;
    dest[1] = '\0';
    return (dest);
}

char        *ft_itoa(int n)
{
    char    *str;
    int        i;
    
    i = (int)ft_number_length(n);
    if (!(str = malloc((i + 1) * sizeof(char))))
        return (NULL);
    str[i--] = '\0';
    if (n == 0)
    {
        str[0] = '0';
        return (str);
    }
    else if (n == -2147483648)
        return (ft_strdup("-2147483648"));
    else if (n < 0)
    {
        str[0] = '-';
        n *= -1;
    }
    while (n > 0)
    {
        str[i--] = '0' + (n % 10);
        n /= 10;
    }
    str[i] = '\0';
    return (str);
}

char *reverse_string(char **src)
{
    char *tmp;
    int str_len;
    int i;
    
    str_len = ft_strlen(*src);
    i = 0;
    if (!(tmp = malloc(sizeof(char) * str_len)))
        return (NULL);
    while (src[str_len] > 0)
        tmp[i++] = *src[str_len--];
    free(src);
    *src = tmp;
    return (*src);
}

char    *ft_strrev(char *src)
{
    int        length;
    int        i;
    char    temp;
    
    length = ft_strlen(src);
    i = -1;
    while (++i < length / 2)
    {
        temp = src[i];
        src[i] = src[length - i - 1];
        src[length - i - 1] = temp;
    }
    return (src);
}

char *num_to_hex(unsigned long long num)
{
    char *res;
    unsigned long long i = 0;
    unsigned long long temp;
    
    if (!(res = malloc(sizeof(char) * ft_number_length(num))))
        return (NULL);
    while (num != 0)
    {
        temp = 0;
        temp = num % 16;
        if (temp < 10)
            res[i++] = temp + 48;
        else
            res[i++] = temp + 55;
        num /= 16;
    }
    ft_strrev(res);
    printf("%s", res);
    return (res);
}
