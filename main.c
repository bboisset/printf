//
//  main.c
//  PrintF
//
//  Created by Boisset on 13/11/2019.
//  Copyright © 2019 Boisset. All rights reserved.
//

#include "printf.h"

/*char *treat_arg(char *str, void *arg)
{
    free(str);
}*/

int is_end_of_arg(char c)
{
    return ((c == 'c' || c == 's' || c == 'p' || c == 'd' || c == 'i' || c == 'u' || c == 'x' || c == 'X' || c == '%') ? 1 : 0);
}

int get_type_by_letter(char c)
{
    if (c == 's' || c == 'p' || c == 'x' || c == 'X')
        return (1);
    else if (c == 'c' || c == 'i' || c == '%')
        return (2);
    else if (c == 'd' || c == 'u')
        return (3);
    return (0);
}

int is_valid_pattern(char **str)//oublie du cumul des pattern
{
    int status;
    
    status = -1;
    if (*str[0] == '0')
        status = zero_pattern(*str);
    else if (*str[0] == '-')
        status = minus_pattern(*str);
    else if (*str[0] == '.')
        status = dot_star_pattern(*str);
    free(*str);
    return (status);
}

char *convert_string(char **str, va_list args, int *args_idx)
{
    char *new_str;
    
    new_str = NULL;
    if (*str[0] == '0')
        new_str = zero_format(*str, args);
    else if (*str[0] == '-')
        new_str = minus_format(*str, args);
    else if (*str[0] == '.')
        new_str = dot_star_format(*str, args);
    free(*str);
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

int parse_string(const char *str, t_list **list, va_list args, int *args_idx)
{
    int i;
    int j;
    int last_addition;
    
    i = 0;
    j = 0;
    last_addition = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '%')
        {
            ft_lstadd_back(list, ft_lstnew(ft_substr(str, last_addition, i - last_addition)));
            if (is_valid_pattern((char**)ft_substr(str, i + 1, j)) == 0)// j should be pattern expected length, i+1 is for removing the %
            {
                ft_lstadd_back(list, ft_lstnew(convert_string((char**)ft_substr(str, i + 1, j), args, args_idx)));
                i += j;
                last_addition = i;
            }
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
    //ft_printf("je suis un test\n", "string", 12);
    printf("je suis une phrase de %-20s, voici un exemple %-10d\n", "test",42);
    //ft_printf("Hello, dddd!\n");
    printf("%%\n");
    printf("%d\n",42);//rend un double
    printf("%i\n\n",42);//rend un int
    
    printf("x : %x\n",1909393);//hexa non signé et lettres miniscules
    printf("X : %X\n\n",1909393);//hexa non signé et lettres majuscules
    
    printf("%u\n",42);
    printf("%x\n",0x12345);

    printf("%c\n",42);
    printf("%s\n","sentence");
    printf("%p\n","sentence");
    
    printf("\n=========   #   ==========\n\n");
    
    printf("%#x | %x\n",0x12345, 0x12345);
    printf("%#x | %x\n",12345, 12345);//le # avec une base x, force le 0x, sauf si commence deja par 0x
    printf("%#o | %o\n",012345,012345);
    printf("%#o | %o\n",12345,12345);// le # avec une base o, force que le (nombre 1) = 0 sauf si (nombre 1) == 0
    
    printf("\n=========   -   ==========\n\n");
    printf("|%-10d| | |%d|\n",235, 235);//cree un espace de la taille du nombre
    printf("|%-10x| | |%x|\n",1909393,1909393);//meme effet
    printf("|%-10%| | |%%|\n");//meme effet
    printf("|%-10s| | |%s|\n","str","str");//meme effet
    printf("|%-10c| | |%c|\n",'c','c');//meme effet
    
    printf("\n=========   0   ==========\n\n");
    printf("|%05d| | |%d|\n",235, 235);//cree un espace de x, x = valeur - taille du %d
    printf("|%010x| | |%x|\n",1909393,1909393);//meme effet
    printf("|%010%| | |%%|\n");//meme effet
    //printf("|%010p| | |%p|\n","str","str");aucun effet
    //printf("|%010c| | |%c|\n",'a','a');aucun effet
    //printf("|%05s| | |%s|\n","str", "str");aucun effet
    printf("|%0-5d| | |%d|\n",235, 235);//le - annule le 0
    
    printf("\n=========   .*   ==========\n\n");
    printf( "%.*f\n", 5, 3.14159265 );//arronndie un float à la valeur fournir en arg1
    printf( "%.*d\n", 5, 42);//meme comportement que le 0
    printf( "%.*s\n", 3, "string");//raccourcie le string à la taille fournir en arg1
    printf( "%.*x\n", 3, 1909393);//aucun effet sur x,X
    return 0;
}
