
#include "minishell.h"

//export with no options


//cases to be careful with
// minishell: export: '123hello' : not a valid identifier
// export _123hello --> works with the underscore at the beginign 
// add the prefix declare -x in front of all the enironment variables
// contrarily to the env command, this lists them in alphabetical order 

// export output when just writing export 
/// _123hello='' // if there is no path, need to replace with single quotes to signal it is to do
//  test=hello

// scenario of two different arguments inside export 
// separated and each will have its own environ,entarea 
// for example 
// export hello world

//ascii order of the variables so lower case goes at the end

//use ft_setenv 

// add the quotes to the path 