/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vaghazar <vaghazar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:51:44 by vaghazar          #+#    #+#             */
/*   Updated: 2022/10/31 13:45:34 by arakhurs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_parse	t_parse;

typedef struct s_spl_pipe
{
	int					is_args;
	int					fd_in;
	int					fd_out;
	int					output_mode;
	int					input_mode;
	int					hdoc_mode;
	int					flag_new_pipe;
	int					tmp;
	char				*hdoc_input;
	pid_t				pid;
	char				**cmd;
	char				*dlm;
	char				**out_files;
	char				**in_files;
	char				**heredoc;
	char				*error_message;
	char				*f_name;
	struct s_spl_pipe	*next;
	struct s_spl_pipe	*prev;
}						t_spl_pipe;

typedef struct s_list_spl_pipe
{
	int					size;
	t_spl_pipe			*head;
	t_spl_pipe			*tail;
}						t_list_spl_pipe;

typedef struct s_env
{
	int					is_export;
	char				*key;
	char				*val;
	struct s_env		*next;
	struct s_env		*prev;
}						t_env;

typedef struct s_list_env
{
	size_t				size;
	t_env				*head;
	t_env				*tail;
}						t_list_env;

typedef struct s_data
{
	int					exit_status;
	int					**hdoc_mode;
	char				*path;
	char				**cmd_paths;
	char				*error_message;
	char				**envp;
	t_parse				*parser;
	t_list_spl_pipe		*cmd_line;
	t_list_env			*env;
	t_list_env			*env_exp;
}						t_data;

typedef struct s_parse
{
	int					l_arr;
	char				*rd_ln;
	char				*key;
	char				**spl_qutoes;
	char				**spl_pipe;
	char				**join_pipe;
	char				**hered_vars;
	t_data				*data;
}						t_parse;

typedef struct s_elem
{
	int					out_file;
	int					in_file;
	int					heredoc;
	int					out_append_files;
}						t_elem;

#endif
