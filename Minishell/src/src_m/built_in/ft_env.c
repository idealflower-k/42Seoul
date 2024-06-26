#include "minishell.h"
#include "defines.h"
#include "envp_command.h"
#include "meta_command.h"
#include "error.h"
#include <errno.h>

int	ft_env(t_simple_cmd *simple_cmd)
{
	const int	len = ft_arrlen((void **)simple_cmd->args);

	if (len == 1)
	{
		print_envp_elem(NULL);
		return (EXIT_SUCCESS);
	}
	else
	{
		prt_err("env: doesn't take args", ERR_ARGS_NUM);
		return (EXIT_FAILURE);
	}
}
