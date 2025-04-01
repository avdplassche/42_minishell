/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:37:54 by jrandet           #+#    #+#             */
/*   Updated: 2025/04/01 11:04:24 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* typedef enum e_whatever         < ---- NORM for enum
{
	ONE,
	TWO,
	THREE
}	t_whatever; */

typedef enum e_standard
{
			STDIN = 0,
			STDOUT = 1,
			STDERR = 2,
}			t_standard;

typedef enum e_error
{
			MALLOC_ERROR = 1,
			CMD_NOT_FOUND = 2,
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
