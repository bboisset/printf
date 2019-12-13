/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:49:17 by bboisset          #+#    #+#             */
/*   Updated: 2019/12/13 23:49:37 by bboisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_flags_state	*init_to_do(void)
{
	t_flags_state	*new;

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

int				assign_type(char c, t_flags_state *to_do)
{
	if (is_end_of_arg(c))
	{
		to_do->type = c;
		return (0);
	}
	return (-1);
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
