/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 14:53:36 by bboisset          #+#    #+#             */
/*   Updated: 2019/12/16 14:12:24 by bboisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include "libft.h"

typedef struct		s_flags_state
{
	int				zero_left;
	int				space_left;
	int				space_right;
	int				end_of_line;
	int				dot_star;
	int				length;
	char			type;
}					t_flags_state;

typedef struct		s_str_edition
{
	int				space_add;
	int				orientation;
	int				charset;
}					t_str_edition;

int					ft_edit_atoi(const char *str, int start);
void				edit_ft_putstr(char *str, int str_len, int end_of_line);
t_flags_state		*init_to_do(void);
t_str_edition		init_str_edition(int space_to_add,
		int orientation, int charset);
char				*num_to_hex(uint64_t num);
char				*handle_ft_strdup(char *str);

int					is_end_of_arg(char c);
char				*get_arguments(char type, va_list args,
		t_flags_state *to_do);
char				*convert_string(va_list args, t_flags_state **to_do);
int					assign_type(char c, t_flags_state *to_do);
int					get_type_by_letter(char c);
int					ft_printf(const char *format, ...);
int					is_end_of_arg(char c);
char				*char_case(va_list args, t_flags_state *to_do);

int					zero_pattern(char *str, int pos, t_flags_state *to_do,
		va_list arg);

int					minus_pattern(char *str, int pos, t_flags_state *to_do,
		va_list arg);

int					is_dot_applicable(char c);
int					dot_pattern(char *str, int pos, t_flags_state *to_do,
		va_list arg);
char				*dot_format(int count, char *str, t_flags_state *to_do);

int					digit_pattern(char *str, int pos, t_flags_state *to_do,
		va_list arg);

char				*add_char(t_str_edition str_edit, char *str, char *prefix);
int					exit_on_error_str_edit(char **pattern,
		t_flags_state **to_do);
char				*exit_on_error_add_char(char **temp, char **prefix,
		int to_free);
int					exit_cvt_str_ft(char **current_arg);
char				*exit_cvt_str(char **current_arg);

#endif
