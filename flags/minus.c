/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:03:27 by bboisset          #+#    #+#             */
/*   Updated: 2019/12/12 15:03:47 by bboisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdarg.h>

int	minus_pattern(char *str, int pos, t_flags_state *to_do, va_list arg)
{
	int	i;
	int	temp;

	i = pos + 1;
	if (str[i] == '*')
	{
		temp = va_arg(arg, int);
		temp = (temp < 0) ? temp * -1 : temp;
		to_do->space_right = temp;
		return (i + 1);
	}
	to_do->space_right = ft_edit_atoi(str, i - 1);
	while (ft_isdigit(str[i]) && str[i] != '\0')
		i++;
	return (i);
}
