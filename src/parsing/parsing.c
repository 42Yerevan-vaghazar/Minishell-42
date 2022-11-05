/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 19:46:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/11/05 16:46:32 by vaghazar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int		g_sig[2] = {0, 0};

int	g_sig = 1;

int	init(t_parse *parser, t_data *data, char **envp)
{
	parser->data = data;
	parser->l_arr = 2;
	parser->key = NULL;
	parser->spl_qutoes = NULL;
	parser->spl_pipe = NULL;
	parser->join_pipe = NULL;
	parser->rd_ln = NULL;
	parser->hered_res = NULL;
	data->parser = parser;
	data->envp = NULL;
	data->hdoc_mode = NULL;
	data->cmd_line = create_list_pipe();
	data->env = create_list_env();
	data->env_exp = create_list_env();
	data->exit_status = 0;
	get_env(data, envp, (EXPORT | ENV));
	shell_lvl(data);
	data->envp = env_cpy(data, data->env);
	return (0);
}
int	free_all(t_data *data)
{
	free_spl_pipe((void *)&data->cmd_line);
	free_parse((void *)&data->parser);
	free_arr(&data->parser->rd_ln);
	return (0);
}
// < b <<a <<t^C r >>t >>p
int	parsing(t_parse *parser)
{
	// int	i;
	if (unexpected_tokens(parser) == START_RD_LN)
		return(START_RD_LN);
	split_quotes(parser);
	rep_vars(parser, 0);
	split_pipe(parser);
	pipe_join(parser);
	get_all_hd_modes(parser);
	find_exe(parser);
	print_info(parser);
	if (parser->data->cmd_line->head == NULL && free_parse(parser))
		return (START_RD_LN);
	ft_clean_all_qutoes(parser->data->cmd_line->head);
	get_hd_mode_in_pipe(parser);
	if ((run_heredoc(parser->data) == START_RD_LN) && free_parse(parser))
		return (START_RD_LN);
	free_parse(parser);
	// free_spl_pipe(&parser->data->cmd_line);
	return (0);
}




// void	sig_term(int signum)
// {
// 	struct termios	termios_p;

// 	// tcgetattr(0, &termios_p);
// 	// termios_p.c_lflag |= ECHOCTL;
// 	// tcsetattr(0, 0, &termios_p);
// 	g_sig = 0;
// 	(void)signum;
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	ioctl(STDIN_FILENO, TIOCSTI, "\n");
// 	// rl_replace_line("", 0);
// 	// rl_on_new_line();
// }

// int	hook_signals(void)
// {
// 	struct sigaction	term;

// 	term.sa_handler = &sig_term;
// 	term.sa_flags = SA_RESTART;
// 	term.sa_mask = 0;
// 	sigaction(SIGINT, &term, NULL);
// 	signal(SIGQUIT, SIG_IGN);
// 	return (0);
// }

int	main(int ac, char **av, char **envp)
{
	t_parse	parser;
	t_data	data;
	int		ps;
	int		i;
	
	(void)av;
	if (ac == 1)
	{
		init(&parser, &data, envp);
		//printf_header();
		// hook_signals();
		while (1)
		{
			// set_term_attr(TC_OFF);
			parser.rd_ln = readline("🔻minishell> ");
			// if (g_sig == 0 && ++g_sig)
				// set_term_attr(TC_ON);
			if (!parser.rd_ln)
			{
				// rl_replace_line("", 0);
				// ft_putstr_fd("exit\n", 0, FREE_OFF);
				// rl_on_new_line();
				// rl_redisplay();
				exit(1);
			}
			if (parser.rd_ln[0])
			{
				add_history(parser.rd_ln);
				if (parsing(&parser) == START_RD_LN && !free_arr(&parser.rd_ln))
					continue ;
				if (data.cmd_line->head && data.cmd_line->head->cmd && data.cmd_line->head->cmd[0])
				{
					ps = data.cmd_line->size;
					i = -1;
					while (i++ < ps)
					{
						if (ps == 1 && ft_strnstr(BUILTINS, data.cmd_line->head->cmd[0], 35))
						{
							ps = 0;
							run_builtins(&data, data.cmd_line->head);
						}
						else
						{
							ps = 0;
							execute(&data);
						}
					}
				}
			}
				// set_env(&data, new_env("?", ft_itoa(data.exit_status), FORME));
			free_spl_pipe(&data.cmd_line);
			free_arr(&parser.rd_ln);
		}
		free_envp(&data.env);
	}
}
