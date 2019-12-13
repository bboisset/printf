/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dot_star.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:02:19 by bboisset          #+#    #+#             */
/*   Updated: 2019/12/13 22:51:32 by bboisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			is_dot_applicable(char c)
{
	return ((c == 's' || c == 'd' || c == 'i' || c == 'u' || c == 'x' ||
				c == 'X') ? 1 : 0);
}

int			dot_pattern(char *str, int pos, t_flags_state *to_do, va_list arg)
{
	int i;
	int temp;

	i = pos + 1;
	if (str[i] == '*')
	{
		temp = va_arg(arg, int);
		temp = (temp < 0) ? temp * -1 : temp;
		to_do->dot_star = temp;
		return (i + 1);
	}
	to_do->dot_star = ft_edit_atoi(str, i - 1);
	while (ft_isdigit(str[i]) && str[i] != '\0')
		i++;
	return (i);
}

static void	dot_exception(char *str, int str_len, int *count,
		t_flags_state *to_do)
{
	*count = (ft_atoi(str) < 1 && to_do->type != 's' && to_do->type != 'x' &&
			to_do->type != 'X' && str_len < *count) ? *count + 1 : *count;
	*count = (to_do->type != 's' && to_do->type != 'x' && to_do->type != 'X' &&
			ft_strncmp(str, "0", str_len) == 0) ? *count - 1 : *count;
	*count = (*count == -1 && to_do->type == 's') ? 0 : *count;
}

char		*dot_format(int count, char *str, t_flags_state *to_do)
{
	int	i;
	int	str_len;

	i = 0;
	str_len = ft_strlen(str);
	dot_exception(str, str_len, &count, to_do);
	if ((to_do->type == 's' && str_len <= count) || (to_do->type != 's' &&
				str_len >= count && str[0] != '0'))
		return (ft_strdup(str));
	else if (count < 1 && ((str[0] == '0' && to_do->type != 's') ||
				(to_do->type == 's')))
		return (ft_substr(str, 1, count));
	else if (count < str_len)
		return (ft_substr(str, 0, count));
	return (add_char(count, str, NULL, 0, '0'));
}

