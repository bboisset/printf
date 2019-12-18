/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edited_ft_libft.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 23:48:02 by bboisset          #+#    #+#             */
/*   Updated: 2019/12/16 14:11:19 by bboisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	edit_ft_putstr(char *str, int str_len, int end_of_line)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == -2 && end_of_line == 1)
		{
			str[i] = '\0';
			end_of_line--;
		}
		i++;
	}
	if (str)
		write(1, str, str_len);
}

char	*handle_ft_strdup(char *str)
{
	if (!str)
		str = "(null)";
	return (ft_strdup(str));
}

int		ft_edit_atoi(const char *str, int start)
{
	int	i;
	int	number;

	i = start;
	number = 0;
	if (str[0] == '\0')
		return (0);
	while (!ft_isdigit(str[i]))
	{
		i++;
		if (str[i] == '\0' || str[i] == '.' || str[i] == '-')
			return (-1);
	}
	while (ft_isdigit(str[i]) && str[i] != '\0')
		number = number * 10 + (str[i++] - '0');
	return (number);
}

char	*char_case(va_list args, t_flags_state *to_do)
{
	char	temp;

	if ((temp = va_arg(args, uintmax_t)) == '\0')
	{
		temp = -2;
		to_do->end_of_line = 1;
	}
	return (ft_char_to_string(temp));
}
