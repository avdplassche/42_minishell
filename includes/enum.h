/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 13:50:24 by alvan-de          #+#    #+#             */
/*   Updated: 2025/02/25 19:41:44 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define BUILTINS "cd,echo,env,exit,export,pwd,unset"
#define DEBUGG_PARSING 1

enum	e_standard
{
		STDIN = 0,
		STDOUT = 1,
		STDERR = 2,
};

enum	e_characters
{
		PIPE = '|',
		IN_REDIR = '<',
		OUT_REDIR = '>',
};

