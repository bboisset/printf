/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digit.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:57:56 by bboisset          #+#    #+#             */
/*   Updated: 2019/12/13 23:32:00 by bboisset         ###   ########.fr       */
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


static char	*minus_edition(char *str, int *negative, int type)
{
	char	*res;
	int		i;

	if (type == 0)
	{
		i = 0;
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

char		*add_char(int space_to_add, char *str, char *prefix,
		int orientation, char charset)
{
	char	*temp;
	char	*new_str;
	int		str_len;
	int		i;
	int		negative;

	i = 0;
	negative = 0;
	str = (prefix != NULL) ? prefix : str;
	if (charset == '0' && str[0] == '-')
	{
		str = minus_edition(str, &negative, 0);
		space_to_add--;
	}
	str_len = ft_strlen(str);
	space_to_add = (space_to_add - str_len > 0) ? space_to_add - str_len : 0;
	if (!(temp = malloc((space_to_add + 1) * sizeof(char))))
		exit_on_error_add_char(&temp, &prefix, 2);
	while (space_to_add > 0)
	{
		temp[i++] = charset;
		space_to_add--;
	}
	temp[i] = '\0';
	if (orientation == 0)
	{
		if (!(new_str = ft_strjoin(temp, str)))
			exit_on_error_add_char(&temp, &prefix, 3);
	}
	else
		if (!(new_str = ft_strjoin(str, temp)))
			exit_on_error_add_char(&temp, &prefix, 3);
	free(temp);
	free(prefix);
	if (negative)
		if (!(new_str = minus_edition(new_str, &negative, 1)))
			return (NULL);
	return (new_str);
}
