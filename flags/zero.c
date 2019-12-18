/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zero.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 14:59:59 by bboisset          #+#    #+#             */
/*   Updated: 2019/12/16 09:31:10 by bboisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

int	zero_pattern(char *str, int pos, t_flags_state *to_do, va_list arg)
{
	int	i;
	int	temp;

	i = pos + 1;
	if (str[i] == '*')
	{
		temp = va_arg(arg, int);
		if (temp > 0)
			to_do->zero_left = temp;
		else
			to_do->space_right = temp * -1;
		return (i + 1);
	}
	to_do->zero_left = ft_edit_atoi(str, i - 1);
	while (ft_isdigit(str[i]) && str[i] != '\0')
		i++;
	return (i);
}
