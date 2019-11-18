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

int    ft_number_length(int nb)
{
    int        length;
    
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

int        ft_strlen(const char *s)
{
    int    i;
    
    i = 0;
    if (!s)
        return (0);
    while (s[i] != '\0')
        i++;
    return (i);
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

static int    ft_isspace(int c)
{
    return (c == ' ' || c == '\t' || c == '\n' || c == '\f' || c == '\r' ||
            c == '\v') ? 1 : 0;
}

int             ft_edit_atoi(const char *str)
{
    int i;
    int negative;
    int number;
    
    i = 0;
    negative = 0;
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

char        *ft_itoa(int n)
{
    char    *str;
    int        i;
    
    i = ft_number_length(n);
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
