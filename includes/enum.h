/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:37:54 by jrandet           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/04/01 11:04:54 by jrandet          ###   ########.fr       */
=======
<<<<<<< HEAD
/*   Updated: 2025/04/01 11:04:24 by alvan-de         ###   ########.fr       */
=======
/*   Updated: 2025/03/31 17:22:47 by jrandet          ###   ########.fr       */
>>>>>>> 9f99c37a067be43a567ff8283017e695fab5431f
>>>>>>> main
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
