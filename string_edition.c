/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_edition.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 16:28:31 by bboisset          #+#    #+#             */
/*   Updated: 2019/12/14 02:30:50 by bboisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char		*get_arguments_pointer(char type, va_list args)
{
	char		*res;
	uintmax_t	temp;

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

char			*get_arguments(char type, va_list args, t_flags_state *to_do)
{
	char	*res;
	char	temp;

	res = NULL;
	if (type == 'u')
		res = ft_itoa_uint64_t(va_arg(args, uint64_t));
	else if (type == 'c')
	{
		if ((temp = va_arg(args, uintmax_t)) == '\0')
			to_do->length += 1;
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
	else if (res == NULL && type == 'p')
		res = ft_strdup("0x0");
	else if (res == NULL)
		res = ft_char_to_string('0');
	return (res);
}

static void		struct_edit(t_flags_state **to_do, char *current_arg)
{
	t_flags_state	*temp;

	temp = *to_do;
	temp->space_left = (temp->type == 'c' && current_arg[0] == 0)
		? temp->space_left - 1 : temp->space_left;
	temp->space_right = (temp->type == 'c' && current_arg[0] == '\0')
		? temp->space_right - 1 : temp->space_right;
	temp->zero_left = (temp->type == 'c' && current_arg[0] == '\0')
		? temp->zero_left - 1 : temp->zero_left;
}

int				convert_string_format(char **c_arg, char **new_str,
		t_flags_state *temp)
{
	struct_edit(&temp, *c_arg);
	if (temp->dot_star != -2 && temp->type != '%' && temp->type != 'c'
			&& temp->type != 'p')
		if (!(*new_str = dot_format(temp->dot_star, *c_arg, temp)))
			return (exit_cvt_str_ft(c_arg));
	if (temp->space_left)
		if (!(*new_str = add_char(init_str_edition(temp->space_left,
							0, ' '), *c_arg, *new_str)))
			return (exit_cvt_str_ft(c_arg));
	if (temp->space_right)
		if (!(*new_str = add_char(init_str_edition(temp->space_right,
							1, ' '), *c_arg, *new_str)))
			return (exit_cvt_str_ft(c_arg));
	if (temp->zero_left)
		if (!(*new_str = add_char(init_str_edition(temp->zero_left, 0,
		((temp->type != 's' && is_dot_applicable(temp->type) &&
		temp->dot_star != -2)) ? ' ' : '0'), *c_arg, *new_str)))
			return (exit_cvt_str_ft(c_arg));
	return (1);
}

char			*convert_string(va_list args, t_flags_state **to_do)
{
	char			*new_str;
	char			*c_arg;
	t_flags_state	*temp;

	temp = *to_do;
	new_str = NULL;
	if (!(c_arg = get_arguments(temp->type, args, temp)))
		return (NULL);
	if (!(convert_string_format(&c_arg, &new_str, temp)))
		return (exit_cvt_str(&c_arg));
	if (temp->first_digit_to_zero)
		new_str = NULL;
	if (new_str == NULL)
		if (!(new_str = ft_strdup(c_arg)))
			return (exit_cvt_str(&c_arg));
	free(c_arg);
	temp->length += ft_strlen(new_str);
	return (new_str);
}
