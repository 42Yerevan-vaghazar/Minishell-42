/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_status_in_env.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 19:31:14 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/12 19:31:24 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_status_in_env(t_data *data, t_parse *parser)
{
	char	*status;

	status = ft_itoa(data->exit_status);
	set_env(data, new_env("?=", status, FORME));
	free_arr(&status);
	free_spl_pipe(&data->cmd_line);
	free_arr(&parser->rd_ln);
	free_parse(parser);
	return (0);
}