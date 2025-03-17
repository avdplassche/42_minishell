
#ifndef DEBUG_H
# define DEBUG_H

int		get_debug_fd();

# define DEBUG(...) dprintf(get_debug_fd(), __VA_ARGS__)
# define DEBUG_CLOSE close(get_debug_fd())

#endif
