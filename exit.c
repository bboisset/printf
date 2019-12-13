/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 22:39:00 by bboisset          #+#    #+#             */
/*   Updated: 2019/12/13 22:39:57 by bboisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		exit_on_error_str_edit(char **pattern, t_flags_state **to_do)
{
	free(*pattern);
	free(*to_do);
	return (-1);
}

char	*exit_on_error_add_char(char **temp, char **prefix, int to_free)
{
	if (to_free == 1 || to_free == 3)
		free(*temp);
	else if (to_free == 2 || to_free == 3)
		free(*prefix);
	return (NULL);
}

char	*exit_cvt_str(char **current_arg)
{
	free(*current_arg);
	return (NULL);
}
