/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboisset <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 23:59:35 by bboisset          #+#    #+#             */
/*   Updated: 2019/12/14 00:01:03 by bboisset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int	main(void){
	printf("test %-12i et %--2.4s %24s !\n", 0, NULL, "coco");
	ft_printf("test %-12i et %--2.4s %24s !\n", 0, NULL, "coco");
	return (0);
}
