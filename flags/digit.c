/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:57:56 by bboisset          #+#    #+#             */
/*   Updated: 2019/12/14 03:21:59 by bboisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

int			digit_pattern(char *str, int pos, t_flags_state *to_do, va_list arg)
{
	int	i;
	int	temp;

	i = pos;
	if (str[i] == '*')
	{
		temp = va_arg(arg, int);
		if (temp > 0)
			to_do->space_left = temp;
		else
			to_do->space_right = temp * -1;
		return (i + 1);
	}
	to_do->space_left = ft_edit_atoi(str, i);
	while (ft_isdigit(str[i]) && str[i] != '\0')
		i++;
	return (i);
}

static char	*minus_edition(char *str, int *negative, int type,
		t_str_edition *str_edit)
{
	char	*res;
	int		i;

	if (type == 0)
	{
		i = 0;
		str_edit->space_add--;
		*negative = 1;
		while (str[i + 1] != '\0')
		{
			str[i] = str[i + 1];
			i++;
		}
		str[i] = '\0';
		return (str);
	}
	else
	{
		res = ft_strjoin("-", str);
		free(str);
		if (!res)
			return (NULL);
		return (res);
	}
}

static char	*add_char_end(t_str_edition str_edit, char **temp, char **prefix,
		char *str)
{
	char	*new_str;

	if (str_edit.orientation == 0)
	{
		if (!(new_str = ft_strjoin(*temp, str)))
			exit_on_error_add_char(temp, prefix, 3);
	}
	else
	{
		if (!(new_str = ft_strjoin(str, *temp)))
			exit_on_error_add_char(temp, prefix, 3);
	}
	free(*temp);
	free(*prefix);
	return (new_str);
}

char		*add_char(t_str_edition str_edit, char *str, char *prefix)
{
	char	*temp;
	char	*new_str;
	int		str_len;
	int		i;
	int		negative;

	i = 0;
	negative = 0;
	str = (prefix != NULL) ? prefix : str;
	if (str_edit.charset == '0' && str[0] == '-')
		str = minus_edition(str, &negative, 0, &str_edit);
	str_len = ft_strlen(str);
	str_edit.space_add =
		(str_edit.space_add - str_len > 0) ? str_edit.space_add - str_len : 0;
	if (!(temp = malloc((str_edit.space_add + 1) * sizeof(char))))
		exit_on_error_add_char(&temp, &prefix, 2);
	while (str_edit.space_add-- > 0)
		temp[i++] = str_edit.charset;
	temp[i] = '\0';
	if (!(new_str = add_char_end(str_edit, &temp, &prefix, str)))
		return (NULL);
	if (negative)
		if (!(new_str = minus_edition(new_str, &negative, 1, &str_edit)))
			return (NULL);
	return (new_str);
}
