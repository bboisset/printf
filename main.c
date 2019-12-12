/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:44:03 by bboisset          #+#    #+#             */
/*   Updated: 2019/12/12 16:40:51 by bboisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		print_list(t_list *list)
{
	int	strlen;

	strlen = 0;
	while (list != NULL)
	{
		ft_putstr(list->content);
		strlen += ft_strlen(list->content);
		list = list->next;
	}
	return (strlen);
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

int		parse_string(const char *str, t_list **list, va_list args)
{
	int				i;
	int				j;
	int				last_addition;
	int				addional_length;
	t_flags_state	*to_do;
	char			*pattern;

	i = 0;
	j = 0;
	addional_length = 0;
	last_addition = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			ft_lstadd_back(list, ft_lstnew(ft_substr(str, last_addition,
							i - last_addition)));
			while ((!is_end_of_arg(str[i + j]) || (str[i + j] == '%' && j == 0))
					&& str[i + j] != '\0')
				j++;
			if (is_valid_pattern(pattern = ft_substr(str, i, j + 1),
						&to_do, args) == 0)
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
	ft_lstadd_back(list, ft_lstnew(ft_substr(str, last_addition,
					i - last_addition)));
	return (addional_length);
}

int		ft_printf(const char *format, ...)
{
	t_list		*list;
	va_list		args;
	int			strlen;
	int			addional_length;

	addional_length = 0;
	va_start(args, format);
	list = NULL;
	addional_length = parse_string(format, &list, args);
	va_end(args);
	strlen = print_list(list) + addional_length;
	ft_lstfree(&list);
	return (strlen);
}
