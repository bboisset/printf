/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:44:03 by bboisset          #+#    #+#             */
/*   Updated: 2019/12/13 23:50:42 by bboisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			is_valid_pattern(char *str, t_flags_state **to_do, va_list args)
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

int			string_edition_end(char **str, int pre_fill_len)
{
	if (!pre_fill_len)
		pre_fill_len = ft_strlen(*str);
	edit_ft_putstr(*str, pre_fill_len);
	free(*str);
	return (pre_fill_len);
}

int			str_to_edit(const char *str, int i, int *total_len, va_list args)
{
	t_flags_state	*to_do;
	char			*pattern;
	char			*temp;
	int				j;

	j = 0;
	while ((!is_end_of_arg(str[i + j]) || (str[i + j] == '%' && j == 0))
			&& str[i + j] != '\0')
		j++;
	if (!(pattern = ft_substr(str, i, j + 1)))
		return (exit_on_error_str_edit(&pattern, &to_do));
	if (is_valid_pattern(pattern, &to_do, args) == 0)
	{
		if (!(temp = convert_string(args, &to_do)))
			return (exit_on_error_str_edit(&pattern, &to_do));
		*total_len += string_edition_end(&temp, to_do->length);
		j += 1;
	}
	free(pattern);
	free(to_do);
	return (j);
}

int			parse_string(const char *str, int *total_len, va_list args)
{
	int		i;
	int		j;
	int		last_addition;
	char	*temp;

	i = 0;
	last_addition = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '%')
		{
			if (!(temp = ft_substr(str, last_addition, i - last_addition)))
				return (-1);
			*total_len += string_edition_end(&temp, 0);
			if ((j = str_to_edit(str, i, total_len, args)) == -1)
				return (-1);
			i += j;
			last_addition = i;
		}
		i = (str[i] != '%') ? i + 1 : i;
	}
	if (!(temp = ft_substr(str, last_addition, i - last_addition)))
		return (-1);
	*total_len += string_edition_end(&temp, 0);
	return (0);
}

int			ft_printf(const char *format, ...)
{
	va_list	args;
	int		total_len;

	total_len = 0;
	va_start(args, format);
	if (parse_string(format, &total_len, args) == -1)
		return (-1);
	va_end(args);
	return (total_len);
}
