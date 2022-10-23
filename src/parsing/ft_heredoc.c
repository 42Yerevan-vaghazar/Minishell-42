/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 21:40:29 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/23 10:31:08 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_strjoin_1(char *s1, char const *s2)
{
	char	*ptr;
	char	*ptr1;
	char	*arr_to_free;

	arr_to_free = s1;
	ptr = (char *) malloc(ft_strlen(s1) + ft_strlen((char *)s2) + 1);
	if (ptr == 0 && !ft_perror("minishell"))
		return (0);
	ptr1 = ptr;
	while (s1 && *s1 != '\0')
		*ptr++ = *s1++;
	while (s2 && *s2 != '\0')
		*ptr++ = *s2++;
	*ptr = '\0';
	return (ptr1);
}

static int	create_hiden_file(t_data *data, char **f_name)
{
	int	i;
	char	*doc;
	int	fd;

	fd  = -1;
	doc = ".42doc";
	i = 0;
	while (!access(ft_strjoin_1(get_env_val(data->env, "TMPDIR"), ft_strjoin_1(doc, ft_itoa(i))), F_OK))
		i++;
	*f_name = ft_strjoin_1(get_env_val(data->env, "TMPDIR"), ft_strjoin_1(doc, ft_itoa(i)));
	fd  = open(*f_name, O_CREAT | O_RDWR | O_TRUNC, 0777);
	if (fd == -1 && ft_perror("minishell"))
		return (-1);
	return (fd);
}

char *ft_heredoc(t_spl_pipe *node, t_parse *parser)
{
	char	*res;
	char	*rd_ln;
	char	*ptr;
	int		i;
	char	*f_name;
	
	res = NULL;
	f_name = NULL;
	i = 0;
	while (node->heredoc[i])
	{	
		free_arr(&node->hdoc_input);
		while (1)
		{
			free_arr(&rd_ln);
			rd_ln = readline(">>");
			if (!rd_ln && !ft_perror("minishell"))
				exit (1);
			if (res)
				res = ft_strjoin(res, "\n");
			if (!ft_strcmp(rd_ln, node->heredoc[i]))
				break;
			res = ft_strjoin(res, rd_ln);
		}
		i++;
		free_arr(&rd_ln);
	}
	if (node->hdoc_mode == HDOC_DQ_MODE)
		rep_vars(parser, &res);
	ft_putstr_fd(res, create_hiden_file(parser->data, &f_name));
	free_arr(&rd_ln);
	return (f_name);
}
