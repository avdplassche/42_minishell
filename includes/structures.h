/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:15:23 by alvan-de          #+#    #+#             */
/*   Updated: 2025/02/24 16:42:26 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_mini
{
	char		**envp;
	char		*current_line;
	int			last_return;
	bool		error;
}				t_mini;

typedef struct s_cmd
{
	char		*bin;
	char		*arg;
	char		*fd_path;
	bool		builtins;
	int			pipe_amount;
	bool		in_redir;
	bool		out_redir;   
	bool		delimiter;     // <<
	bool		out_appredir;  // >>
	// t_mini		*mini;
}				t_cmd;
