/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrandet <jrandet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 17:37:27 by jrandet           #+#    #+#             */
/*   Updated: 2025/03/21 17:37:34 by jrandet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEBUG_H
# define DEBUG_H

int		get_debug_fd(void);

# define DEBUG(...) dprintf(get_debug_fd(), __VA_ARGS__)
# define DEBUG_CLOSE close(get_debug_fd())

#endif
