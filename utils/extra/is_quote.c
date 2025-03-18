
#include "minishell.h"

/** Is c a quote charactere ?
 * @param c a character
 * @return 1 for yes, 2 for no
 * @note 34 =  "
 * @note 39 =  '
 */
int	is_quote(char c)
{
	if (c == 34 || c == 39)
		return (1);
	return (0);
}
