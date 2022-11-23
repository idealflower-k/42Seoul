/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sanghwal <sanghwal@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 13:48:15 by sanghwal          #+#    #+#             */
/*   Updated: 2022/11/23 17:51:08 by sanghwal         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd	**parsing_av(int total, char **av, char *envp[])
{
	t_cmd	**cmd_arr;
	char	**envp_path;
	int		i;

	envp_path = parsing_envp(envp);
	cmd_arr = ft_malloc(sizeof(t_cmd *) * (total + 1));
	cmd_arr[total] = 0;
	i = 0;
	while (i < total)
	{
		cmd_arr[i] = ft_malloc(sizeof(t_cmd));
		ft_memset(cmd_arr[i], 0, sizeof(t_cmd));
		cmd_arr[i]->cmd_info = ft_split(av[i], ' ');
		cmd_arr[i]->cmd_path = get_path(cmd_arr[i]->cmd_info[0], envp_path);
		if (cmd_arr[i]->cmd_path)
			cmd_arr[i]->executable = 1;
		cmd_arr[i]->total_cmd = total;
		i++;
	}
	i = 0;
	while (envp_path[i])
		free(envp_path[i++]);
	free(envp_path);
	return (cmd_arr);
}

char	*get_path(char *cmd, char **envp_path)
{
	char	*path;
	int		i;

	path = 0;
	i = 0;
	while (envp_path && envp_path[i])
	{
		path = make_cmd_path(cmd, envp_path[i]);
		if (access(path, F_OK | X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	perror("Comand not found");
	return (0);
}

char	*make_cmd_path(char *cmd, char *envp_path)
{
	char	*tmp;
	char	*result;

	tmp = 0;
	result = 0;
	tmp = ft_strjoin(envp_path, "/");
	result = ft_strjoin(tmp, cmd);
	free(tmp);
	return (result);
}

char	**parsing_envp(char *envp[])
{
	char	**result;
	int		i;

	result = 0;
	i = 0;
	while (envp[i])
	{
		if (ft_memcmp(envp[i], "PATH=", 5) == 0)
			result = ft_split(&envp[i][5], ':');
		i++;
	}
	return (result);
}
