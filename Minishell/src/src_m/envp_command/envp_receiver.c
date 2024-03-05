#include "minishell.h"
#include "defines.h"
#include "envp_command.h"
#include "meta_command.h"

t_hash_elem	*envp_receiver(\
	t_envp_flags flag, const char *key, const char *val, const char *option)
{
	t_hash_table	*envp;

	envp = get_envp();
	if (flag == SET)
		hash_insert(envp, key, val);
	else if (flag == GET)
		return (hash_get(envp, key));
	else if (flag == DEL)
		hash_delete(envp, key);
	else if (flag == PRINT)
		hash_print_all(option, envp);
	return (NULL);
}
