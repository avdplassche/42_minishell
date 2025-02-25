/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 16:15:23 by alvan-de          #+#    #+#             */
/*   Updated: 2025/02/25 19:28:39 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/** A structure containing minishell related variables
 * @param envp local environment variables (execve's 3rd parameter for ex)
 * @param builtins list of builtins functions
 * @param current_line current prompt to work with
 * @param last_return sig return of the last cmd (needed for $?)
 * @param error to be configured
 */
typedef struct s_mini
{
	char		**envp;
	char		**builtins;
	char		*current_line;
	int			last_return;
	bool		error;
}				t_mini;

/** A structure containing command's 'token'
 * @param bin the name of the binary to execute
 * @param arg arguments given to the binary
 * @param fd_path path if needed by the binary
 * @param pipe_amount amount of pipes in the command
 * @param number id of the command (1 == first exec)
 * @param builtin is the binary a builtin that we need to code ?
 * @param in_redir is there an input redirection in the command
 * @param out_redit is there an output redirection in the command
 * @param delimiter is there a delimiter in the command (<<)
 * @param out_appredir is there an out_appredir in the command (>>)
 * @param index used to remember where we stopped the parsing
 */
typedef struct s_cmd
{
	char		*bin;
	char		**args;
	char		*fd_path;
	int			pipe_amount;
	int			id;
	int			builtin;
	bool		in_redir;
	bool		out_redir;
	bool		delimiter;
	bool		out_appredir;
	int			index;
}				t_cmd;
