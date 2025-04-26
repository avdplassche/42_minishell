/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_debug_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alvan-de <alvan-de@student.42lausanne.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 13:01:33 by alvan-de          #+#    #+#             */
/*   Updated: 2025/04/26 13:01:36 by alvan-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_debug_fd(void)
{
	static int fd = -1;

	if (fd == -1)
		fd = open("./log/debug.log", O_CREAT | O_RDWR | O_TRUNC, 0664);
	return (fd);
}
