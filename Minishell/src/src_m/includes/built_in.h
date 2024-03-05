#ifndef BUILT_IN_H
# define BUILT_IN_H

int		s_built_in_exec(t_tree_node *root, t_executor *execute);
int		built_in(t_simple_cmd *simple_cmd, t_simple_cmd_type type);

int		ft_echo(t_simple_cmd *simple_cmd);
int		ft_cd(t_simple_cmd *simple_cmd);
int		ft_pwd(t_simple_cmd *simple_cmd);
int		ft_export(t_simple_cmd *simple_cmd);
int		ft_unset(t_simple_cmd *simple_cmd);
int		ft_env(t_simple_cmd *simple_cmd);
int		ft_exit(t_simple_cmd *simple_cmd);

t_bool	is_valid_params(char c);

#endif