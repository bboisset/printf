/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:44:03 by bboisset          #+#    #+#             */
/*   Updated: 2019/12/12 23:37:32 by bboisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_list(t_list *list)
{
	int	len;

	len = 0;
	while (list != NULL)
	{
		edit_ft_putstr(list->content, list->str_len);
		len += list->str_len;
		list = list->next;
	}
	return (len);
}

int		assign_type(char c, t_flags_state *to_do)
{
	if (is_end_of_arg(c))
	{
		to_do->type = c;
		return (0);
	}
	return (-1);
}

int		is_valid_pattern(char *str, t_flags_state **to_do, va_list args)
{
	int	i;

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

void	parse_string(const char *str, t_list **list, va_list args)
{
	int				i;
	int				j;
	int				last_addition;
	t_flags_state	*to_do;
	char			*temp;

	i = 0;
	j = 0;
	last_addition = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			temp = ft_substr(str, last_addition, i - last_addition);
			ft_lstadd_back(list, ft_lstnew(temp, ft_strlen(temp)));
			while ((!is_end_of_arg(str[i + j]) || (str[i + j] == '%' && j == 0))
					&& str[i + j] != '\0')
				j++;
			if (is_valid_pattern(temp = ft_substr(str, i, j + 1),
						&to_do, args) == 0)
			{
				ft_lstadd_back(list, ft_lstnew(convert_string(args, &to_do),
							to_do->length));
				j += 1;
			}
			free(to_do);
			i += j;
			last_addition = i;
			j = 0;
			free(temp);
		}
		else
			i++;
	}
	temp = ft_substr(str, last_addition, i - last_addition);
	ft_lstadd_back(list, ft_lstnew(temp, ft_strlen(temp)));
}

int		ft_printf(const char *format, ...)
{
	t_list		*list;
	va_list		args;
	int			len;

	va_start(args, format);
	list = NULL;
	parse_string(format, &list, args);
	va_end(args);
	len = print_list(list);
	ft_lstfree(&list);
	return (len);
}
