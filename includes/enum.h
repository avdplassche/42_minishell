/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:57:13 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/26 11:51:27 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum e_error
{
			MALLOC_ERROR = 1,
			CMD_NOT_FOUND = 2,
			PIPE_ERROR = 3,
			FORK_ERROR = 4,
			DUP_ERROR = 5,
}			t_error;

typedef enum e_redirections
{
			IN_REDIR,
			OUT_REDIR,
			HERE_DOC,
			OUT_APPEND,
}			t_redirections;

typedef enum e_command
{
			INVALID = -1,
			USER = 0,
			BUILTIN = 1,
}			t_command;
