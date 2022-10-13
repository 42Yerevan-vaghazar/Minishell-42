/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_elem.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 18:41:52 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/13 19:55:24 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_elem	*count_elem(char *str)
{
	int	i;
	int count;
	t_elem	*res;

	i = 0;
	res = malloc(sizeof(t_elem));
	res->heredoc = 1;
	res->out_append_files = 1;
	res->out_file = 1;
	res->in_file = 1;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<' && ++i && ++i)
			res->heredoc++;
		if (str[i] == '>' && str[i + 1] == '>' && ++i && ++i)
			res->out_append_files++;
		if (str[i] == '<' && ++i)
			res->in_file++;
		if (str[i] == '>' && ++i)
			res->out_file++;
		if (str[i])
			i++;
	}
	// printf("iii = %d\n", i);
	return (res);
}