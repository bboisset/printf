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

char *get_arguments(char type, va_list args)
{
    char *res;
    unsigned long long test;
    
    if (type == 'c')
        res = ft_char_to_string(va_arg(args, uintmax_t));
    else if (type == 's')
        res = va_arg(args, char*);
    else if (type == 'p' || type == 'x' || type == 'X')
    {
        test = va_arg(args, unsigned long long);
        res = num_to_hex(test);
    }
    return NULL;
}

char *convert_string(char **str, va_list args, int *args_idx, t_flags_state **to_do)
{
    char *new_str = NULL;
    char *current_arg;
    t_flags_state *temp;
    
    temp = *to_do;
    current_arg = get_arguments(temp->type, args);
    if (temp->zero_left)
        new_str = NULL;
    else if (temp->space_left)
        new_str = NULL;
    else if (temp->space_right)
        new_str = NULL;
    else if (temp->first_digit_to_zero)
        new_str = NULL;
    else if (temp->dot_star)
        new_str = NULL;
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

void assign_type(char c, t_flags_state *to_do)
{
    to_do->type = c;
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
        if (str[i] == 0)
            i = zero_pattern(str, i, *to_do);
        else if (ft_isdigit(str[i]))
            i = digit_pattern(str, i, *to_do);
        else if (str[i] == '-')
            i = minus_pattern(str, i, *to_do);
        else if (str[i] == '.')
            i = dot_star_pattern(str, i, *to_do);
        i++;
    }
    assign_type(str[i - 1], *to_do);
    free(str);//can't access to free
    return (0);
}

int parse_string(const char *str, t_list **list, va_list args, int *args_idx)
{
    int i;
    int j;
    int last_addition;
    t_flags_state *to_do;
    
    i = 0;
    j = 0;
    last_addition = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '%')
        {
            ft_lstadd_back(list, ft_lstnew(ft_substr(str, last_addition, i - last_addition)));
            while (!is_end_of_arg(str[i + j]) || (str[i + j] == '%' && !(str[i + j - 1] == '%')))
                j++;
            if (is_valid_pattern((char*)ft_substr(str, i, j + 1), &to_do) == 0)//possible impossible to free
            {
                ft_lstadd_back(list, ft_lstnew(convert_string((char**)ft_substr(str, i, j + 1), args, args_idx, &to_do)));
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
    char *x = "string";
    printf("%p\n",x);
    ft_printf("%p\n", x);
    /*printf("je test, %#-10x", 12345);
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
    printf( "%.*x\n", 3, 1909393);//aucun effet sur x,X*/
    return 0;
}
