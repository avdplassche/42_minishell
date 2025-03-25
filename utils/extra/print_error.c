
#include "minishell.h"

void	print_error(const char *format, const char *path)
{
	char	buffer[1024];
	char	*ptr;

	ptr = buffer;
	while (*format && *format != '%')
	{
		*ptr++ = *format++;
	}
	if (*format == '%' && *(format + 1) == 's')
	{
		format += 2;
		while (*path)
		{
			*ptr++ = *path++;
		}
	}
	while (*format)
	{
		*ptr++ = *format++;
	}
	*ptr = '\0';
	write(2, buffer, ft_strlen(buffer));
}
