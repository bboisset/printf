/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:49:17 by bboisset          #+#    #+#             */
/*   Updated: 2019/12/12 23:10:30 by bboisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags_state	*init_to_do(void)
{
	t_flags_state *new;

	if (!(new = (t_flags_state*)malloc(sizeof(t_flags_state))))
		return (NULL);
	new->zero_left = 0;
	new->space_left = 0;
	new->space_right = 0;
	new->zero_left = 0;
	new->first_digit_to_zero = 0;
	new->dot_star = -2;
	new->length = 0;
	new->type = '0';
	return (new);
}

void			edit_ft_putstr(char *str, int str_len)
{
	if (str)
		write(1, str, str_len);
}

char			*handle_ft_strdup(char *str)
{
	if (!str)
		str = "(null)";
	return (ft_strdup(str));
}

int				ft_edit_atoi(const char *str, int start)
{
	int i;
	int number;

	i = start;
	number = 0;
	if (str[0] == '\0')
		return (0);
	while (!ft_isdigit(str[i]))
	{
		i++;
		if (str[i] == '\0')
			return (-1);
	}
	while (ft_isdigit(str[i]) && str[i] != '\0')
		number = number * 10 + (str[i++] - '0');
	return (number);
}

char			*num_to_hex(uint64_t num)
{
	char		*res;
	uint64_t	i;
	uint64_t	temp;

	i = 0;
	if (num == 0)
		return (ft_strdup("0"));
	if (!(res = malloc(sizeof(char) * ft_number_length(num))))
		return (NULL);
	while (num != 0)
	{
		temp = num % 16;
		if (temp < 10)
			res[i++] = temp + 48;
		else
			res[i++] = temp + 55;
		num /= 16;
	}
	res[i] = '\0';
	ft_strrev(res);
	return (res);
}
