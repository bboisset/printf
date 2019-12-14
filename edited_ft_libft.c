/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edited_ft_libft.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 23:48:02 by bboisset          #+#    #+#             */
/*   Updated: 2019/12/13 23:55:45 by bboisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	edit_ft_putstr(char *str, int str_len)
{
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
